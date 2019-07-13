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

// �u���b�N�쐬
template<class T>
void* createBlock(T &obj) {
	Valkyrie::Memory::BoundaryBlock<> *b1 = new(memory + lastPos) Valkyrie::Memory::BoundaryBlock<>(sizeof(T));
	lastPos += b1->getBlockSize();
	void *p = b1->getMemory();
	return new(p) T();
}

int voidtest1_main()
{
	// Block��4�쐬
	printf("---- Block��4�쐬 ----\n");
	createBlock(MyClassA());
	createBlock(MyClassB());
	createBlock(MyClassC());
	createBlock(MyClassD());

	// �������u���b�N�̍ŏ����猟�����Ă݂悤
	printf("\n---- �C�e���[�g ----\n");
	Valkyrie::Memory::BoundaryBlock<> *block = (Valkyrie::Memory::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 4; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// ������߂��Ă݂悤
	printf("\n---- �t�C�e���[�g ----\n");
	block = block->prev();
	for (unsigned i = 4; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i-1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	// 2�Ԗڂ̃u���b�N��3�ԖڂƂ��}�[�W���悤
	printf("\n---- B2-B3 �}�[�W ----\n");
	block = block->next(); // 2�Ԗڂ�
	block->marge();
	new(block->getMemory()) MyClassMarge();

	// �}�[�W��̃u���b�N���ŏ����猟�����Ă݂悤
	printf("\n---- �C�e���[�g ----\n");
	block = (Valkyrie::Memory::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 3; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// ������߂��Ă݂悤
	printf("\n---- �t�C�e���[�g ----\n");
	block = block->prev();
	for (unsigned i = 3; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i - 1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	// 2�Ԗڂ̃u���b�N�̕������s
	printf("\n---- �}�[�W�u���b�N�̕������s ----\n");
	Valkyrie::Memory::BoundaryBlock<> *b2 = block->next(); // 2�Ԗڂ�
	if (!b2->enableSplit(sizeof(MyClassB) + 100))
		printf("�������s�i�����������j\n");

	// 2�Ԗڂ̃u���b�N�𕪊����܂�
	printf("\n---- �}�[�W�u���b�N�𕪊� ----\n");
	b2 = block->next(); // 2�Ԗڂ�
	Valkyrie::Memory::BoundaryBlock<> *b3 = b2->split(sizeof(MyClassB));
	new(b2->getMemory()) MyClassB();
	new(b3->getMemory()) MyClassC();

	// �������u���b�N�̍ŏ����猟�����Ă݂悤
	printf("\n---- �C�e���[�g ----\n");
	block = (Valkyrie::Memory::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 4; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// ������߂��Ă݂悤
	printf("\n---- �t�C�e���[�g ----\n");
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
// BoundaryTag.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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

// �u���b�N�쐬
template<class T>
void* createBlock(T &obj) {
	Dix::BoundaryBlock<> *b1 = new(memory + lastPos) Dix::BoundaryBlock<>(sizeof(T));
	lastPos += b1->getBlockSize();
	void *p = b1->getMemory();
	return new(p) T();
}

int voidtest1_main()
{
	// Block��4�쐬
	printf("---- Block��4�쐬 ----\n");
	createBlock(MyClassA());
	createBlock(MyClassB());
	createBlock(MyClassC());
	createBlock(MyClassD());

	// �������u���b�N�̍ŏ����猟�����Ă݂悤
	printf("\n---- �C�e���[�g ----\n");
	Dix::BoundaryBlock<> *block = (Dix::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 4; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// ������߂��Ă݂悤
	printf("\n---- �t�C�e���[�g ----\n");
	block = block->prev();
	for (unsigned i = 4; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i-1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	// 2�Ԗڂ̃u���b�N��3�ԖڂƂ��}�[�W���悤
	printf("\n---- B2-B3 �}�[�W ----\n");
	block = block->next(); // 2�Ԗڂ�
	block->marge();
	new(block->getMemory()) MyClassMarge();

	// �}�[�W��̃u���b�N���ŏ����猟�����Ă݂悤
	printf("\n---- �C�e���[�g ----\n");
	block = (Dix::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 3; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// ������߂��Ă݂悤
	printf("\n---- �t�C�e���[�g ----\n");
	block = block->prev();
	for (unsigned i = 3; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i - 1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	// 2�Ԗڂ̃u���b�N�̕������s
	printf("\n---- �}�[�W�u���b�N�̕������s ----\n");
	Dix::BoundaryBlock<> *b2 = block->next(); // 2�Ԗڂ�
	if (!b2->enableSplit(sizeof(MyClassB) + 100))
		printf("�������s�i�����������j\n");

	// 2�Ԗڂ̃u���b�N�𕪊����܂�
	printf("\n---- �}�[�W�u���b�N�𕪊� ----\n");
	b2 = block->next(); // 2�Ԗڂ�
	Dix::BoundaryBlock<> *b3 = b2->split(sizeof(MyClassB));
	new(b2->getMemory()) MyClassB();
	new(b3->getMemory()) MyClassC();

	// �������u���b�N�̍ŏ����猟�����Ă݂悤
	printf("\n---- �C�e���[�g ----\n");
	block = (Dix::BoundaryBlock<>*)memory;
	for (unsigned i = 0; i < 4; i++) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i, pObj->name, block->getMemorySize());
		block = block->next();
	}

	// ������߂��Ă݂悤
	printf("\n---- �t�C�e���[�g ----\n");
	block = block->prev();
	for (unsigned i = 4; i != 0; i--) {
		MyClassBase* pObj = (MyClassBase*)block->getMemory();
		printf("%d: %s(%d)\n", i - 1, pObj->name, block->getMemorySize());
		block = block->prev();
	}

	return 0;
}



#endif