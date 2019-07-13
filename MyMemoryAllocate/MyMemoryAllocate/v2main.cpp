#if 0
//
#include "Valkyrie/Memory/BoundaryBlock.h"
#include "string.h"
#include "stdio.h"

struct MyClassBase {
	char name[16];
	MyClassBase(const char* n) {
		memset(name, 0 ,sizeof(name));
		memcpy(name, n, strlen(n) + 1);
	}
};

struct MyClassA : MyClassBase {
	unsigned val;
	MyClassA() : MyClassBase("MyClassA"), val(0xAA) {}
};

struct MyClassB : MyClassBase {
	unsigned val1, val2;
	MyClassB() : MyClassBase("MyClassB"), val1(0xBB), val2(0x3BB3) {}
};

struct MyClassC : MyClassBase {
	unsigned val1, val2, val3;
	MyClassC() : MyClassBase("MyClassC"), val1(0xCC), val2(0x4CC4), val3(0x4CCCC4) {}
};

struct MyClassD : MyClassBase {
	unsigned val1, val2, val3, val4;
	MyClassD() : MyClassBase("MyClassD"), val1(0xDD), val2(0x5DD5), val3(0x5DDDD5), val4(0x5DDDDDD5) {}
};

struct MyClassMarge : MyClassBase {
	MyClassMarge() : MyClassBase("MyClassMarge") {}
};

char memory[1024];
unsigned lastPos = 0;

// ブロック作成
template<class T>
void* createBlock(T &obj) {
	Valkyrie::Memory::BoundaryBlock<> *b1 = new(memory + lastPos) Valkyrie::Memory::BoundaryBlock<>(sizeof(T));
	lastPos += b1->getBlockSize();
	void *p = b1->getMemory();
	return new(p) T();
}

int voidtest1_main()
{
	// Blockを4つ作成
	printf("---- Blockを4つ作成 ----\n");
	createBlock(MyClassA());
	createBlock(MyClassB());
	createBlock(MyClassC());
	createBlock(MyClassD());

	// メモリブロックの最初から検索してみよう
	printf("\n---- イテレート ----\n");
	Valkyrie::Memory::BoundaryBlock<> *block = (Valkyrie::Memory::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 4; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// 検索を戻ってみよう
	printf("\n---- 逆イテレート ----\n");
	block = block->prev();
	for (unsigned i = 4; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i-1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	// 2番目のブロックと3番目とをマージしよう
	printf("\n---- B2-B3 マージ ----\n");
	block = block->next(); // 2番目へ
	block->marge();
	new(block->getMemory()) MyClassMarge();

	// マージ後のブロックを最初から検索してみよう
	printf("\n---- イテレート ----\n");
	block = (Valkyrie::Memory::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 3; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// 検索を戻ってみよう
	printf("\n---- 逆イテレート ----\n");
	block = block->prev();
	for (unsigned i = 3; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i - 1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	// 2番目のブロックの分割失敗
	printf("\n---- マージブロックの分割失敗 ----\n");
	Valkyrie::Memory::BoundaryBlock<> *b2 = block->next(); // 2番目へ
	if (!b2->enableSplit(sizeof(MyClassB) + 100))
		printf("分割失敗（正しい挙動）\n");

	// 2番目のブロックを分割します
	printf("\n---- マージブロックを分割 ----\n");
	b2 = block->next(); // 2番目へ
	Valkyrie::Memory::BoundaryBlock<> *b3 = b2->split(sizeof(MyClassB));
	new(b2->getMemory()) MyClassB();
	new(b3->getMemory()) MyClassC();

	// メモリブロックの最初から検索してみよう
	printf("\n---- イテレート ----\n");
	block = (Valkyrie::Memory::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 4; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// 検索を戻ってみよう
	printf("\n---- 逆イテレート ----\n");
	block = block->prev();
	for (unsigned i = 4; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i - 1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	return 0;
}



#endif
#if 0
// BoundaryTag.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//
#include "BoundaryBlock.h"
#include "string.h"
#include "stdio.h"

struct MyClassBase {
	char name[16];
	MyClassBase(const char* n) {
		memset(name, 0 ,sizeof(name));
		memcpy(name, n, strlen(n) + 1);
	}
};

struct MyClassA : MyClassBase {
	unsigned val;
	MyClassA() : MyClassBase("MyClassA"), val(0xAA) {}
};

struct MyClassB : MyClassBase {
	unsigned val1, val2;
	MyClassB() : MyClassBase("MyClassB"), val1(0xBB), val2(0x3BB3) {}
};

struct MyClassC : MyClassBase {
	unsigned val1, val2, val3;
	MyClassC() : MyClassBase("MyClassC"), val1(0xCC), val2(0x4CC4), val3(0x4CCCC4) {}
};

struct MyClassD : MyClassBase {
	unsigned val1, val2, val3, val4;
	MyClassD() : MyClassBase("MyClassD"), val1(0xDD), val2(0x5DD5), val3(0x5DDDD5), val4(0x5DDDDDD5) {}
};

struct MyClassMarge : MyClassBase {
	MyClassMarge() : MyClassBase("MyClassMarge") {}
};

char memory[1024];
unsigned lastPos = 0;

// ブロック作成
template<class T>
void* createBlock(T &obj) {
	Dix::BoundaryBlock<> *b1 = new(memory + lastPos) Dix::BoundaryBlock<>(sizeof(T));
	lastPos += b1->getBlockSize();
	void *p = b1->getMemory();
	return new(p) T();
}

int voidtest1_main()
{
	// Blockを4つ作成
	printf("---- Blockを4つ作成 ----\n");
	createBlock(MyClassA());
	createBlock(MyClassB());
	createBlock(MyClassC());
	createBlock(MyClassD());

	// メモリブロックの最初から検索してみよう
	printf("\n---- イテレート ----\n");
	Dix::BoundaryBlock<> *block = (Dix::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 4; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// 検索を戻ってみよう
	printf("\n---- 逆イテレート ----\n");
	block = block->prev();
	for (unsigned i = 4; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i-1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	// 2番目のブロックと3番目とをマージしよう
	printf("\n---- B2-B3 マージ ----\n");
	block = block->next(); // 2番目へ
	block->marge();
	new(block->getMemory()) MyClassMarge();

	// マージ後のブロックを最初から検索してみよう
	printf("\n---- イテレート ----\n");
	block = (Dix::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 3; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// 検索を戻ってみよう
	printf("\n---- 逆イテレート ----\n");
	block = block->prev();
	for (unsigned i = 3; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i - 1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	// 2番目のブロックの分割失敗
	printf("\n---- マージブロックの分割失敗 ----\n");
	Dix::BoundaryBlock<> *b2 = block->next(); // 2番目へ
	if (!b2->enableSplit(sizeof(MyClassB) + 100))
		printf("分割失敗（正しい挙動）\n");

	// 2番目のブロックを分割します
	printf("\n---- マージブロックを分割 ----\n");
	b2 = block->next(); // 2番目へ
	Dix::BoundaryBlock<> *b3 = b2->split(sizeof(MyClassB));
	new(b2->getMemory()) MyClassB();
	new(b3->getMemory()) MyClassC();

	// メモリブロックの最初から検索してみよう
	printf("\n---- イテレート ----\n");
	block = (Dix::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 4; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// 検索を戻ってみよう
	printf("\n---- 逆イテレート ----\n");
	block = block->prev();
	for (unsigned i = 4; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i - 1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	return 0;
}



#endif