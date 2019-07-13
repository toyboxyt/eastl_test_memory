#if 0 // error vs2012
#include <new>

template <class T>
struct MyAllocator {
    // 要素の型
    using value_type = T;

    // 特殊関数
    // (デフォルトコンストラクタ、コピーコンストラクタ
    //  、ムーブコンストラクタ)
    MyAllocator() {}

    // 別な要素型のアロケータを受け取るコンストラクタ
    template <class U>
    MyAllocator(const MyAllocator<U>&) {}

    // メモリ確保
    T* allocate(std::size_t n)
    {
        return reinterpret_cast<T*>(std::malloc(sizeof(T) * n));
    }

    // メモリ解放
    void deallocate(T* p, std::size_t n)
    {
        static_cast<void>(n);
        std::free(p);
    }
};

// 比較演算子
template <class T, class U>
bool operator==(const MyAllocator<T>&, const MyAllocator<U>&)
{ return true; }

template <class T, class U>
bool operator!=(const MyAllocator<T>&, const MyAllocator<U>&)
{ return false; }

#include <vector>
#include <list>
int c11alotest_main()
{
    std::vector<int, MyAllocator<int>> v = {1, 2, 3};
    std::list<int, MyAllocator<int>> ls = {4, 5, 6};
}
#endif