
#if 0
#include <iostream>
#include <vector>

using namespace std;

class log_allocator{
public:
	typedef int value_type;
	typedef int* pointer;
	typedef size_t size_type;

	pointer allocate(size_type n)
	{
		pointer p  = new int[n];
		cout << "allocate "  << p << " : " << n << endl;
		return nullptr;
	}
	void deallocate(pointer p, size_type n)
	{
		cout << "deallocate " << p << " : "  << n << endl;
	}
};

void c01_custorm_main(){

	vector<int, log_allocator> iv;
	iv.push_back(1);

}
#endif