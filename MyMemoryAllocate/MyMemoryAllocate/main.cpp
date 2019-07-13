//#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__) 
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__) 

#include "vtestmain.h"
//extern void StackMemoryTest_main();
//extern void StackMemoryTest_main_boost();
//extern void AllocatorVerctorTestMain();
//extern int c11alotest_main();
//extern int ThreadBoostMemory_Main();
//extern void c01_custorm_main();

//extern int voidtest1_main();


int main(){

//	voidtest1_main();
//	c01_custorm_main();
	Test01::vtest_main();
	//StackMemoryTest_main_boost();
	//StackMemoryTest_main();
//	AllocatorVerctorTestMain();

//	c11alotest_main();
	//ThreadBoostMemory_Main();
	return 0;
}

