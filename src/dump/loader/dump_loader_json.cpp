
#include "dump_loader_json.h"

#include <fstream>

CDumpLoaderJson::CDumpLoaderJson()
    : CDumpLoader("CDumpLoaderJson")
{   
}

CDumpLoaderJson::~CDumpLoaderJson()
{
}

CDumpLoaderJson *
CDumpLoaderJson::clone()
{
    return new CDumpLoaderJson();
}

bool 
CDumpLoaderJson::open(const std::string &_name)
{        
    Json::Reader reader;
    
    std::ifstream file(_name);
    file >> m_root;
    
    std::cout << "CDumpLoaderJson::open() class = " << m_root["class"] << std::endl;
        
    return true;
}

// example of json members
//{
//  "name": "m_name",
//  "type": "std::string",
//  "value": "Tsemac is the name"
//}
bool 
CDumpLoaderJson::load(const std::string &_type, const std::string &_name, u_int &_value)
{
    
    return true;
}

bool 
CDumpLoaderJson::load(const std::string &_type, const std::string &_name, std::string &_value)
{
    
    return true;
}

void
CDumpLoaderJson::close()
{
}

