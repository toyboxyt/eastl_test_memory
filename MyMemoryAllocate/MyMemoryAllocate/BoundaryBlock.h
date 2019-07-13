#ifndef IKD_DIX_BOUNDARYBLOCK_H
#define IKD_DIX_BOUNDARYBLOCK_H

// BoundaryBlockクラス
//
//  HEADERはユーザ定義の前方タグで、
//  メモリ管理部分のサイズを保持するメンバがあれば成立します。
//  ENDTAGは整数サイズの代入演算子があれば拡張も出来ます。

#include <new.h>

namespace Dix {
	////////////////////////////////
	// BondaryBlock用ヘッダーファイル（例）
	//
	class BoundaryBlockHeader {
		unsigned size;
	public:
		BoundaryBlockHeader() : size() {}
		unsigned getSize() {return size;}
		void setSize(unsigned size) {this->size = size;}
	};


	////////////////////////////////
	// Boundaryblockクラス
	//
	template<class HEADER = BoundaryBlockHeader, class ENDTAG = unsigned>
	class BoundaryBlock {
		HEADER header;

		// 後端タグを書き込み
		void writeEndTag() {
			new((char*)this + getBlockSize() - getEndTagSize()) ENDTAG(getBlockSize());
		}

		// 後端タグサイズを取得
		unsigned getEndTagSize() {
			return sizeof(ENDTAG);
		}

	public:
		BoundaryBlock(unsigned size) {
			header.setSize(size);
			writeEndTag();
		};

		// 管理メモリへのポインタを取得
		void* getMemory() {
			return (char*)this + sizeof(BoundaryBlock);
		}

		// 管理メモリサイズを取得
		unsigned getMemorySize() {
			return header.getSize();
		}

		// ブロックサイズを取得
		unsigned getBlockSize() {
			return sizeof(BoundaryBlock) + header.getSize() + getEndTagSize();
		}

		// 次のブロックへのポインタを取得
		BoundaryBlock *next() {
			return (BoundaryBlock*)((char*)this + getBlockSize());
		}

		// 前のブロックへのポインタを取得
		BoundaryBlock *prev() {
			unsigned *preSize = (unsigned*)((char*)this - getEndTagSize());
			return (BoundaryBlock*)((char*)this - *preSize);
		}

		// 右ブロックをマージ
		void marge() {
			// 右ブロックを取得
			BoundaryBlock *nextBlock = next();
			// タグを変更
			unsigned newSize = header.getSize() + getEndTagSize() +
				sizeof(BoundaryBlock) +	nextBlock->getMemorySize();
			header.setSize(newSize);
			writeEndTag();
		}

		// ブロックを分割
		BoundaryBlock *split(unsigned size) {
			// 新規ブロックを作るサイズが無ければNULL
			unsigned needSize = size + getEndTagSize() + sizeof(BoundaryBlock);
			if (needSize > header.getSize())
				return 0;

			// 新規ブロックのメモリサイズを算出
			unsigned newBlockMemSize = header.getSize() - needSize;

			// 既存サイズを引数サイズに縮小
			header.setSize(size);
			writeEndTag();

			// 新規ブロックを作成
			BoundaryBlock *newBlock = next();
			new (newBlock) BoundaryBlock(newBlockMemSize);

			return newBlock;
		}

		// 指定サイズに分割可能？
		bool enableSplit(unsigned size) {
			// 新規ブロックを作るサイズが無ければNULL
			unsigned needSize = size + getEndTagSize() + sizeof(BoundaryBlock);
			if (needSize > header.getSize())
				return false;
			return true;
		}
	};
}

#endif
