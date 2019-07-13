#include "BoundaryTagBlock.h"

//�R���X�g���N�^
BoundaryTagBlock::BoundaryTagBlock():
flag(false),size(0),p(0),c(0){
	prev=next=this;//������
}
BoundaryTagBlock::BoundaryTagBlock(char * dataP,unsigned int size)
	:flag(false),p(dataP){
	prev=next=this;	//������
	this->size=size;//�^�p�������T�C�Y
	if(p!=0){
		//c��p����size��������ɂ���I�[�^�O���w��
		c=(unsigned int*)(dataP+size);
		*c=sizeof(BoundaryTagBlock)+size+sizeof(unsigned int);//��L����S������
	}
	else{c=0;}
}
//�f�X�g���N�^
BoundaryTagBlock::~BoundaryTagBlock(){}

//�^�p�f�[�^�T�C�Y���擾
unsigned int BoundaryTagBlock::GetDataSize(){
	return size;
}

//���g����L����S�Ẵf�[�^�T�C�Y���擾
unsigned int BoundaryTagBlock::GetAllSize(){
	return *c;
}

//�o�������X�g�֓����
BoundaryTagBlock* BoundaryTagBlock::Regist(BoundaryTagBlock* nbp){
	//�Ăяo�����͏�Ƀ_�~�[���X�g�̐擪�u���b�N
	nbp->next=next;
	nbp->prev=this;
	nbp->prev->next=nbp->next->prev=nbp;
	return this;
}

//�o�������X�g�𔲂���
BoundaryTagBlock* BoundaryTagBlock::Remove(){
	prev->next=next;
	next->prev=prev;
	prev=next=this;
	return this;
}
