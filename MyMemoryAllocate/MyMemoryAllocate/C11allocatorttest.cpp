#if 0 // error vs2012
#include <new>

template <class T>
struct MyAllocator {
    // �v�f�̌^
    using value_type = T;

    // ����֐�
    // (�f�t�H���g�R���X�g���N�^�A�R�s�[�R���X�g���N�^
    //  �A���[�u�R���X�g���N�^)
    MyAllocator() {}

    // �ʂȗv�f�^�̃A���P�[�^���󂯎��R���X�g���N�^
    template <class U>
    MyAllocator(const MyAllocator<U>&) {}

    // �������m��
    T* allocate(std::size_t n)
    {
        return reinterpret_cast<T*>(std::malloc(sizeof(T) * n));
    }

    // ���������
    void deallocate(T* p, std::size_t n)
    {
        static_cast<void>(n);
        std::free(p);
    }
};

// ��r���Z�q
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