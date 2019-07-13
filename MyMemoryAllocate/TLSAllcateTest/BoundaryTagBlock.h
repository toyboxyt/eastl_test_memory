#pragma once



class BoundaryTagBlock
{
public:

	bool flag;
	unsigned int size;
	char* p;
	unsigned int * c;
	BoundaryTagBlock *prev,*next;//BoundaryTagBlock�̑o�������X�g


	BoundaryTagBlock();
	BoundaryTagBlock(char * dataP,unsigned int size);
	//�f�X�g���N�^
	~BoundaryTagBlock();

	//�^�p�f�[�^�T�C�Y���擾
	unsigned int  GetDataSize();
	//���g����L����S�Ẵf�[�^�T�C�Y���擾
	unsigned int  GetAllSize();
	//�o�������X�g�֓����
	BoundaryTagBlock* Regist(BoundaryTagBlock* nbp);
	//�o�������X�g�𔲂���
	BoundaryTagBlock* Remove();
};
typedef BoundaryTagBlock BBlock;