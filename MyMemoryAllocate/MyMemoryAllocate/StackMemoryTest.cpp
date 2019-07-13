#include "crtdbg.h"
//#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__) 
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__) 

#include <vector>

#include <boost/progress.hpp>
#include <boost/scoped_ptr.hpp>
//#include <boost/shared_ptr.hpp>
#include "Valkyrie/Memory/StackAllocator.h"



/// --------------------------------------------------
/// http://aaa568.blog76.fc2.com/blog-entry-31.html


///スタックアロケータ作った  http://gamedevelopmentmemo.blog.fc2.com/blog-entry-14.html
/// --------------------------------------------------


class TestA{
public:
	void init(){
		fdata.init();
	}

	struct data{
		int a;
		int b;
		float px;
		float py;
		float pz;

		void init(){
			a = 2;
			b = 99;
		}
	};

	data fdata;
};

class TestAB{
public:
	void init(){
		fdata.init();
	}

	int getSize(){
		return fdata.size();
	}

	struct data{
		int a;
		int b;
		float px;
		float py;
		float pz;

		//std::vector<float> v1;
		//float* v1;

		void init(){
			a = 2;
			b = 99;

			//v1 = new float[3];
			//v1.push_back(11);
			//v1.push_back(2);
			//v1.push_back(31);
		}

		int size(){
			int s = 
				sizeof(a)
				+ sizeof(b)
				+ sizeof(px)
				+ sizeof(py)
				+ sizeof(pz)
				;
			//s += sizeof(v1)*sizeof(float);
			return s;
		}
	};

	data fdata;
};

//char buf[9999999]={};

void StackMemoryTest_main_boost(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_DELAY_FREE_MEM_DF|_CRTDBG_CHECK_ALWAYS_DF|_CRTDBG_LEAK_CHECK_DF);

	
	const Valkyrie::s32 SIZE = 1024; // 1k
	const Valkyrie::s32 MSIZE = SIZE*1024; // 1M
	const Valkyrie::s32 GSIZE = MSIZE *1024; // 1G
	const Valkyrie::s32 _TSIZE = SIZE; // 1G

	Valkyrie::c1* buf;
	buf = (Valkyrie::c1*)std::malloc(sizeof(Valkyrie::c1) * _TSIZE);
	std::unique_ptr<void, decltype(&std::free)> abuf(buf, std::free);
	//	std::unique_ptr<void, decltype(&std::free)>::pointer buf = abuf.get();


	{
		boost::progress_timer pt;
		{
#if 0
			Valkyrie::u32 maxcount = _TSIZE / sizeof(TestA);
			for( int i = 0; i < maxcount; i++){
				Valkyrie::u32 possize = sizeof(TestA)*i; 
				TestA* t1;
				t1 = new(buf+possize)TestA();
				t1->init();
				//boost::shared_ptr<TestA> spt(t1);
				//spt->init();
			}
#endif

#if 1
			int iii = 999;
			Valkyrie::u32 lastpos = 0;
			Valkyrie::u32 maxcount = _TSIZE / sizeof(TestAB);
			for( int i = 0; i < maxcount; i++){
				Valkyrie::u32 possize = lastpos;//sizeof(TestAB)*i; 
				TestAB* t1;
				t1 = new(buf+possize)TestAB();
				t1->init();
				lastpos += t1->getSize();//sizeof(t1);
			}
#endif

		}
		int iiij= 999;

	}
}

void StackMemoryTest_main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_DELAY_FREE_MEM_DF|_CRTDBG_CHECK_ALWAYS_DF|_CRTDBG_LEAK_CHECK_DF);

	TestA* t1;
	const Valkyrie::s32 SIZE = 1024; // 1k
	const Valkyrie::s32 MSIZE = SIZE*1024; // 1M
	const Valkyrie::s32 GSIZE = MSIZE *1024; // 1G
	const Valkyrie::s32 _TSIZE = MSIZE; // 1G

	Valkyrie::c1* buf;
	buf = (Valkyrie::c1*)std::malloc(sizeof(Valkyrie::c1) * _TSIZE);

	//	std::unique_ptr<void, decltype(&std::free)> buf(std::malloc(sizeof(Valkyrie::c1) * _TSIZE), std::free);


#if 1
	{
		boost::progress_timer pt;
		{
			//			Valkyrie::Memory::StackAllocator s1(buf, _TSIZE);

			Valkyrie::u32 maxcount = _TSIZE / sizeof(TestA);
			for( int i = 0; i < maxcount; i++){
				Valkyrie::u32 possize = sizeof(TestA)*i; 
				t1 = new(buf+possize)TestA();
				t1->init();
			}

#if 0
			TestA* t1 = (TestA*)(s1.Allocate(sizeof(TestA)));
			t1->init();
			//while(1){

			//	break;
			//}
#endif

			int iii = 999;

		}
		int iiij= 999;

	}
#endif
	std::cout << "free call " << std::endl;
	std::free(buf);
	std::cout << "freed " << std::endl;

	//	t1->init();

	//	t1 = new TestA();

}
