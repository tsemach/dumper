#ifndef __TEST_SERIALIZER_DUMMY_H
#define __TEST_SERIALIZER_DUMMY_H

#pragma once

#include <string>

//#include <iostream>

class CBase {
public:

	std::string m_base_name;
	size_t	m_base_size;	 
};

class CMore {
public:
	CMore() {
		m_cmore_size = 333;
		m_cmore_name = std::string("cmore class name");
	}
	int 		m_cmore_size;
	std::string m_cmore_name;

private:
};

class CData {
public:
    CData() : m_buff("empty") {
    }
    
	const char   *m_buff;
	size_t	m_size;
	CMore	m_more;	 
};

//#pragma test "(include = test_dummy.dump)"
class CTest : public CBase {
public:
	CTest() {
        m_data = new CData();
		m_id = 100;
	}

	void print();
	int x;

	u_int 		m_id;
	CData 	   *m_data;
	std::string m_name;	

private:
	u_int		m_private;
};

#endif //
