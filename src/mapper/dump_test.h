
#ifndef CDUMPTEST_H
#define CDUMPTEST_H

#include <string>

class CBase {
public: 
    CBase() {
        x_base = 0x5a5a;        
    }
    
    void print();
    
private:
    int x_base;
};

class CTest : public CBase {
public:
	CTest();
   ~CTest();

	void print();
	void set(int i);
	void name(const std::string &_name);

private:
	std::string m_name;
	int m_number;
};

#endif /* CDUMPTEST_H */

