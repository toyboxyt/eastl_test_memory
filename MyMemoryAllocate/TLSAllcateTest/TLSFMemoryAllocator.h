#pragma once
#include <boost/integer.hpp>

class TLSFMemoryAllocator
{
private:
	static const int N=2;
	boost::uint16_t allSize;
	boost::uint16_t allAloSize;
	boost::uint8_t baseMem;


public:
	TLSFMemoryAllocator(void);
	~TLSFMemoryAllocator(void);
};

