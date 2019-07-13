#if 0
#include <stdio.h>


//STL用メモリ管理
void* Malloc(size_t size);
void Free(void* ptr, size_t size);//size：メモリの確保サイズ、Mallocのsize

// <xmemory0> allocatorを改造

// STL用自作アロケータ
template<class _Ty>
class Allocator
{  // generic allocator for objects of class _Ty
public:
	typedef Allocator<_Ty> other;

	typedef _Ty value_type;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef void *void_pointer;
	typedef const void *const_void_pointer;

	typedef value_type& reference;
	typedef const value_type& const_reference;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	template<class _Other>
	struct rebind
	{	// convert this type to allocator<_Other>
		typedef Allocator<_Other> other;
	};

	pointer address(reference _Val) const 
	{	// return address of mutable _Val
		return (_STD addressof(_Val));
	}

	const_pointer address(const_reference _Val) const 
	{	// return address of nonmutable _Val
		return (_STD addressof(_Val));
	}

	Allocator() throw()
	{	// construct default allocator (do nothing)
	}

	Allocator(const Allocator<_Ty>&) throw()
	{	// construct by copying (do nothing)
	}

	template<class _Other>
	Allocator(const Allocator<_Other>&) throw()
	{	// construct from a related allocator (do nothing)
	}

	template<class _Other>
	Allocator<_Ty>& operator=(const Allocator<_Other>&)
	{	// assign from a related allocator (do nothing)
		return (*this);
	}

	void deallocate(pointer _Ptr, size_type _Count)
	{	// deallocate object at _Ptr
		Free(_Ptr, _Count*sizeof (_Ty));
	}

	pointer allocate(size_type _Count)
	{	// allocate array of _Count elements
		void *_Ptr = 0;

		if (_Count == 0)
			;
		else if (((size_t)(-1) / sizeof (_Ty) < _Count)
			|| (_Ptr = Malloc(_Count * sizeof (_Ty))) == 0)
			std::_Xbad_alloc();	// report no memory

		return ((_Ty *)_Ptr);
	}

	pointer allocate(size_type _Count, const void *)
	{	// allocate array of _Count elements, ignore hint
		return (allocate(_Count));
	}

	void construct(_Ty *_Ptr)
	{	// default construct object at _Ptr
		::new ((void *)_Ptr) _Ty();
	}

	void construct(_Ty *_Ptr, const _Ty& _Val)
	{	// construct object at _Ptr with value _Val
		::new ((void *)_Ptr) _Ty(_Val);
	}

	template<class _Uty>
	void destroy(_Uty *_Ptr)
	{	// destroy object at _Ptr
		_Ptr->~_Uty();
	}

	size_t max_size() const throw()
	{	// estimate maximum array size
		return ((size_t)(-1) / sizeof (_Ty));
	}
};

// Allocatorが同じものかどうか
template<class _Ty, class _Other> inline
	bool operator==(const Allocator<_Ty>& _Left,
	const Allocator<_Other>& _Right) throw()
{   // test for allocator equality
	return sizeof(_Ty)==sizeof(_Other);
	//サイズが同じであれば、２つのアロケータは同じもの
	//もしMalloc,Free関数ではなく::operator new deleteを使用した場合
	//どの型でも同じアロケータになるため常にreturn true;
}

template<class _Ty,
class _Other> inline
	bool operator!=(const Allocator<_Ty>& _Left,
	const Allocator<_Other>& _Right) throw()
{   // test for allocator inequality
	return !(Left==Right);
}




	//// vector
	//template <class TYPE>
	//struct Vector
	//{
	//	typedef std::vector<TYPE, Allocator<TYPE>> T;
	//};
void AllocatorVerctorTestMain(){


	//// string
	//typedef std::basic_string<char, std::char_traits<char>,Allocator<char>> String;
	//typedef std::basic_string<wchar_t, std::char_traits<wchar_t>,Allocator<wchar_t>> WString;

	//// map
	//template <class KEY, class TYPE, class PR = std::less<KEY>>
	//struct Map
	//{
	//	typedef std::map<KEY, TYPE, PR, Allocator<std::pair<const KEY, TYPE>>> T;
	//};

	////VS2012(Update2)では未対応のエイリアステンプレートでの定義
	//template <TYPE>
	//using Vector = std::vector<TYPE, Allocator<TYPE>>;
}
#endif