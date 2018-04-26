
#include <iostream>
#include <cstddef>
#include <vector>
#include <string>
#include <exception>

class CSerializer;

class CBase {
friend class CSerializer;
public:    
    CBase() {
        x_base = 1010;
    }
    
private:
    int x_stam;
    int x_base;
};

#pragma dump ('include = cnone.dump')       
class CNone : public CBase {
friend class CSerializer;   
public:
    CNone() {
        x_none = 2020;
        x_name = "TSEMACHTSEMACHTSEMACHTSEMACHTSEMACHTSEMACHTSEMACHTSEMACHTSEMACH";
    }
    
    #pragma dump getter('x_name')
    void print() {
        std::cout << "CNone::print() in print x_none = " << x_none << std::endl; 
    }
    
private: 
    int x_none;
    std::string x_name;
    std::string x_more;
};

// serialize of CNone
class CSerializerCNone : public CSerializer {
public:    
    
    bool serialize(CNone &_none, "dump_none.json") {
        serialize("u_int", "m_id", _none.m_none)
    }
    
    bool serialize(type, name, value) {
        
    }
};
    
class CData {
friend class CSerializer;    
public:
    CData() {
        x = 100;
        names.push_back(std::string("name1"));
        names.push_back(std::string("name2"));
    }
    
private:    
    int x;
    std::vector<std::string>    names;
};

#pragma test library = 'fwcloud_test'
class CSerializer {
public:
    CSerializer() {}
   ~CSerializer() {}
    
   void print(CData &_data) {
        std::cout << "CSerializer::print() x = "  << _data.x << std::endl;
        for (auto s : _data.names) {
            std::cout << "CSerializer::print() name = "  << s << std::endl;
        }
        CNone none;
    
        std::cout << "main() CNone offset of x = " << offsetof(CNone, x_base) << std::endl;
        std::cout << "main() CNone offset of x = " << offsetof(CNone, x_none) << std::endl;
        std::cout << "main() CNone offset of x = " << offsetof(CNone, x_name) << std::endl;
        std::cout << "main() CNone offset of x = " << offsetof(CNone, x_more) << std::endl;

        std::cout << "main() CNone address of x = " << *((int *)&(none.x_base)) << std::endl;
        std::cout << "main() CNone address of x = " << offsetof(CNone, x_none) << std::endl;
        std::string *p_string = reinterpret_cast<std::string *>((void *)&(none.x_name));
        std::cout << "main() CNone address of name = " << none.x_name << std::endl;
        std::cout << "main() CNone address of x = " << offsetof(CNone, x_more) << std::endl;
   }
private:
};

int
main(int argc, char *argv[])
{
    std::cout << "main() start main" << std::endl;
    
    CSerializer s;
    CData       d;
    
    s.print(d);       
  
    return 0;
}


