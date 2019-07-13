#include "Valkyrie/Memory/MemoryMaster.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
#include <list>

#include "Valkyrie/Memory/Allocator.h"
#include "Valkyrie/Memory/MemoryAllocator.h"
#define Max(a,b) (a<b) ? b : a

void vmain() {
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//int aaa = Max(sizeof(long long), 2);
	//int jj = 9;
	//jj = 1;

	//int* ms = (int*)malloc(sizeof(int));
	//int* jj2 = new int;

	//unsigned *i = (unsigned *)Valkyrie::Allocator(sizeof(unsigned));

#if 0
	{
		using namespace Valkyrie;
		printf("alloc(sizeof(unsigned), 1024, 4); call\n");
		Valkyrie::MemoryMaster::leakReport();

		Allocator alloc(sizeof(unsigned), 1024, 4);
		unsigned *i = reinterpret_cast<unsigned *>(alloc.Allocate());

		*i = 0u;

		alloc.Free(i);

	}
#endif
#if 0
	{
		using namespace Valkyrie;
		printf("Allocate call\n");
		Valkyrie::MemoryMaster::leakReport();

		unsigned *i = (unsigned *)Allocate(sizeof(unsigned));

		*i = 330u;

		Free(i, sizeof(unsi));
	}
#endif

#if 0

	{
		using namespace Valkyrie;

		unsi *i = New<unsi>();
		*i = 9u;
		Delete(i);
	}

	
#endif


#if 1
	// STL
	{

		printf("1 call\n");
		Valkyrie::MemoryMaster::leakReport();
		std::vector<int> mv;
		mv.push_back(1);
		printf("2 call\n");
		Valkyrie::MemoryMaster::leakReport();
		//mv.push_back(2);
		//mv.push_back(3);
		//mv.push_back(4);

		//std::list<int> ml;
		//ml.push_back(1);
		//ml.push_back(2);
		//ml.push_back(3);

		printf("3 call\n");
		Valkyrie::MemoryMaster::leakReport();

	}
#endif


#if 0
	{
		using namespace Valkyrie;
		std::vector<int, Valkyrie::allocator<int>> myVector;
		myVector.push_back(1);
		myVector.push_back(2);
		myVector.push_back(3);

		std::list<int, Valkyrie::allocator<int>> myList;
		myList.push_back(1);
		myList.push_back(2);
		myList.push_back(3);
	}
#endif

	{
		Valkyrie::FreeAll();
	}
//	Valkyrie::MemoryMaster::FreeGMP();
}

void testboost_pool() {

}

void main() {
	vmain();
}