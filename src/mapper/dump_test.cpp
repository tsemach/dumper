
#include "dump_test.h"

#include <iostream>

void
CBase::print()
{
   std::cout << "CBase::print() x_base = " << x_base << std::endl;
}

CTest::CTest() 
    : m_number(0) 
{
}

CTest::~CTest()
{
}

void 
CTest::print() 
{
    CBase::print();
	std::cout << "CTest::print() m_name = " << m_name << std::endl;
	std::cout << "CTest::print() m_number = " << m_number << std::endl;
}

void 
CTest::set(int i) 
{ 
	m_number = i;
}
	
void 
CTest::name(const std::string &_name) 
{
		m_name = _name;	
}		