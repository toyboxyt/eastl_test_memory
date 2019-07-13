#if 0 // POOLTEST
#include "vtestmain.h"
#include "Valkyrie/Const/valkyrieConst.h"
#include "Valkyrie/Memory/MemoryPool.h"
#include <boost/progress.hpp>
#include "Valkyrie/Utility.h"


namespace Valkyrie{

	class AA:public MemoryPool::AppendMemoryPool<int[100], 100>{
	public:
		AA(int a){
			dummy[99] = a;
		}

		int get() const {return dummy[99];}

	private:
		int dummy[100];
	};

	class BB{
	public:
		BB(int a){
			dummy[99] = a;
		}

		int get() const {return dummy[99];}

	private:
		int dummy[100];
	};
	
}

namespace Test01{


	 int vtest_main() {

		 const int NUMX = 10000; 
		 Valkyrie::MemoryPool::AppendMemoryPool<int[100],100>::init();
		{
			boost::progress_timer t;
			for( int i = 0; i < NUMX; i ++){
				Valkyrie::AA* ptr = new Valkyrie::AA(i);
				delete ptr;
			}
		}
		{
			boost::progress_timer t;
			for( int i = 0; i < NUMX; i ++){
				Valkyrie::BB* ptr = new Valkyrie::BB(i);
				delete ptr;
			}
		}

		return 0;
	}


}
#endif

#if  1
#include "crtdbg.h"

#include "vtestmain.h"
#include "Valkyrie/Const/valkyrieConst.h"
#include "Valkyrie/Memory/MemoryMaster.h"
#include <boost/progress.hpp>
#include "Valkyrie/Utility.h"


namespace Valkyrie{

	struct AllocInfo{
		u32 fullSize;		// メモリブロック総サイズ
		void* freeMemPtr;	// フリーメモリブロックへのポインタ

	};

	struct MemInfo{
		u32 size;
		c1* getMem(){
			return (c1*)this + sizeof(MemInfo);
		}
	};
/*
	void maintedstmemory(){
		AllocInfo ai;
		ai.fullSize = 999;

		MemInfo mi;
		mi.size  = 1;

	}
*/
}

//inline void* operator new(std::size_t size) {
//	void* allocPtr = NULL;
//	allocPtr = std::malloc(size);
//	return allocPtr;
//}

namespace Test01{

	struct Test{
		Valkyrie::s32 a, b;
		Valkyrie::f32 c;
		Test():a(99),b(32),c(30.354){
		}
	};
	struct Block{
		int blocki;
		float px;
		Block(int size){
			blocki = size;
			px = 9;
		}
		int getBlockSize(){
			return sizeof(this);
		}
	};

	struct Vec{
		Valkyrie::f32 x,y,z;
	};
	struct UVVec{
		Valkyrie::f32 u, v;
	};
	
	struct TestList{
		Valkyrie::s32 a, b;
		Valkyrie::f32 c;
		Vec v[250];
		UVVec uv[128];
			
		TestList():a(99),b(32),c(30.354)
		{
			//v = new Vec[2];
		}

		int getBlockSize(){
			return sizeof(TestList);
		}
	};


	 int vtest_main() {
		 _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_DELAY_FREE_MEM_DF|_CRTDBG_CHECK_ALWAYS_DF|_CRTDBG_LEAK_CHECK_DF);


		//{
		//	boost::progress_timer t;
		//	for( int i = 0; i < 100; i ++){
		//		Test *test = new Test;
		//		delete test;
		//	}

		//}
		////Valkyrie::maintedstmemory();
		//{
		//	boost::progress_timer t;
		//	char memoryBlock[1024]={};
		//	unsigned lastPos = 0;

		//	Block *newBlock = new(memoryBlock)Block(32);
		//	lastPos += newBlock->getBlockSize();
		//	printf("%d \n", lastPos);
		//}
		{
			boost::progress_timer t;
			char memoryBlock[100000]={};
			unsigned lastPos = 0;

			TestList *newBlock = new TestList();
			lastPos += newBlock->getBlockSize();
			printf("%d \n", lastPos);
			delete newBlock;
		}

		return 0;
	}


}
#endif