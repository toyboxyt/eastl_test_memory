#pragma once



class BoundaryTagBlock
{
public:

	bool flag;
	unsigned int size;
	char* p;
	unsigned int * c;
	BoundaryTagBlock *prev,*next;//BoundaryTagBlockの双方向リスト


	BoundaryTagBlock();
	BoundaryTagBlock(char * dataP,unsigned int size);
	//デストラクタ
	~BoundaryTagBlock();

	//運用データサイズを取得
	unsigned int  GetDataSize();
	//自身が占有する全てのデータサイズを取得
	unsigned int  GetAllSize();
	//双方向リストへ入れる
	BoundaryTagBlock* Regist(BoundaryTagBlock* nbp);
	//双方向リストを抜ける
	BoundaryTagBlock* Remove();
};
typedef BoundaryTagBlock BBlock;