
#include <iostream>
#include <cstddef>

#include "dump_serializer_test.h"
#include "dump_loader_test.h"
#include "test_serializer_dummy.h"

class COffsetBase {
public:
	std::string m_offset_string;
};

class COffset {
public:

	void print() {
		std::cout << "COffset::print() size of m_int = " << sizeof(m_offset_int1) << " offset of m_int1 = " << offsetof(COffset, m_offset_int1) << std::endl;
        std::cout << "COffset::print() size of m_int = " << sizeof(m_offset_int2) << " offset of m_int2 = " << offsetof(COffset, m_offset_int2) << std::endl;
        std::cout << "COffset::print() size of m_int = " << sizeof(m_offset_int3) << " offset of m_int3 = " << offsetof(COffset, m_offset_int3) << std::endl;
		std::cout << "COffset::print() size of m_string = " << sizeof(m_string) << " offset of m_string = " << offsetof(COffset, m_string) << std::endl;
	}
	
	int             m_offset_int1;
    int             m_offset_int2;
    int             m_offset_int3;
	std::string		m_string;
private:
};


//#define __attribute__(test)

#pragma test ('library = mylist') 
int
main(int argc, char *argv[])
{
	std::cout << argv[0] << ": enter to .." << std::endl;

	COffset o;
	o.print();

		
	CDumpSerializerTest runner;

    std::cout << argv[0] << ": before test declaration:" << std::endl;
	CTest t;
	
	t.x = 100;
	t.m_id = 200;
	t.m_name = "Tsemach is the name";

    std::cout << argv[0] << ": going to dump t:" << std::endl;
	runner.dump<CTest>(t, std::string("dump_dummy.json"));

	CDumpLoaderTest loader;
	CTest l;
	loader.load<CTest>(l, std::string("dump_dummy.json"));
	l.print();

	return 0;
}
