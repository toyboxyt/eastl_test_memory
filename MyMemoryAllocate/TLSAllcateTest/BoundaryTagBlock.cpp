#include "BoundaryTagBlock.h"

//コンストラクタ
BoundaryTagBlock::BoundaryTagBlock():
flag(false),size(0),p(0),c(0){
	prev=next=this;//初期化
}
BoundaryTagBlock::BoundaryTagBlock(char * dataP,unsigned int size)
	:flag(false),p(dataP){
	prev=next=this;	//初期化
	this->size=size;//運用メモリサイズ
	if(p!=0){
		//cはpからsizeだけ後方にある終端タグを指す
		c=(unsigned int*)(dataP+size);
		*c=sizeof(BoundaryTagBlock)+size+sizeof(unsigned int);//占有する全メモリ
	}
	else{c=0;}
}
//デストラクタ
BoundaryTagBlock::~BoundaryTagBlock(){}

//運用データサイズを取得
unsigned int BoundaryTagBlock::GetDataSize(){
	return size;
}

//自身が占有する全てのデータサイズを取得
unsigned int BoundaryTagBlock::GetAllSize(){
	return *c;
}

//双方向リストへ入れる
BoundaryTagBlock* BoundaryTagBlock::Regist(BoundaryTagBlock* nbp){
	//呼び出し元は常にダミーリストの先頭ブロック
	nbp->next=next;
	nbp->prev=this;
	nbp->prev->next=nbp->next->prev=nbp;
	return this;
}

//双方向リストを抜ける
BoundaryTagBlock* BoundaryTagBlock::Remove(){
	prev->next=next;
	next->prev=prev;
	prev=next=this;
	return this;
}
