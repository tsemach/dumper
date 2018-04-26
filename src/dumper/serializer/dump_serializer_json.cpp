
#include "dump_serializer_json.h"

#include <fstream>
#include <json/writer.h>

CDumpSerializerJson::CDumpSerializerJson()
    : CDumpSerializer("CDumpSerializerJson"), m_curr(&m_root), m_dept(0)
{   
}

CDumpSerializerJson::~CDumpSerializerJson()
{
}

CDumpSerializerJson *
CDumpSerializerJson::clone()
{
    return new CDumpSerializerJson();
}

bool 
CDumpSerializerJson::open(const std::string &_name)
{    
    m_name = _name;
    m_root.clear();
    m_curr = &m_root;
    
    m_root["decl"] = "Record";
    m_root["type"] = "CTest";
    m_root["version"] = "1.0";
    m_root["members"] = Json::Value();    
    m_curr = &(m_root["members"]);
    m_path.push_back("CTest");
    m_dept = 1;
        
    return true;
}

// example of json members
//{
//  "name": "m_name",
//  "type": "std::string",
//  "value": "Tsemac is the name"
//}
bool 
CDumpSerializerJson::serialize(const CDumpASTNode &_node, u_int _value)
{
    Json::Value member;
    
    std::cout << "CDumpSerializerJson::serialize(u_int):" << __LINE__ << " enter to .. u_int" << std::endl;
    
    if ( ! m_curr ) {
        return false;
    }
    member["type"] = _node.getTypeName();
    member["name"] = _node.getVarxName();
    member["value"] = _value;
    
    (*m_curr)[_node.getVarxName()] = member;    
    std::cout << "CDumpSerializerJson::serialize(u_int):" << __LINE__ << " exit from .. u_int" << std::endl;
    return true;
}

bool 
CDumpSerializerJson::serialize(const CDumpASTNode &_node, char * _value)
{
    Json::Value member;
    
    std::cout << "CDumpSerializerJson::serialize(char *):" << __LINE__ << " enter to .. char *" << std::endl;
    if ( ! m_curr ) {        
        return false;
    }    
    std::cout << "CDumpSerializerJson::serialize(char *):" << __LINE__ << " _value = "  << std::endl;
    member["type"] = _node.getTypeName();
    member["name"] = _node.getVarxName();
    _value != nullptr ? member["value"] = _value : member["value"] = "nullptr";    
    
    std::cout << "CDumpSerializerJson::serialize(char *):" << __LINE__ << " exit from " << std::endl;
    
    (*m_curr)[_node.getVarxName()] = member;    
    
    return true;
}

bool 
CDumpSerializerJson::serialize(const CDumpASTNode &_node, const std::string &_value)
{
    Json::Value member;
    std::cout << "CDumpSerializerJson::serialize(std::string):" << __LINE__ << " enter to .. name = " << _node.getVarxName() << std::endl;    
    
    if ( ! m_curr ) {
        return false;
    }
    std::cout << "CDumpSerializerJson::serialize(std::string):" << __LINE__ << " _value = " << _value << std::endl;    
    member["type"] = _node.getTypeName();
    member["name"] = _node.getVarxName();
    member["value"] = _value;
        
    (*m_curr)[_node.getVarxName()] = member;
    std::cout << "CDumpSerializerJson::serialize(std::string):" << __LINE__ << " exit from .. name = " << _node.getVarxName() << std::endl;    
    
    return true;
}

bool 
CDumpSerializerJson::addRecord(const CDumpASTNode &_node)
{
    std::cout << "CDumpSerializerJson::addRecord():" << __LINE__ << " enter to .. m_path size = " << m_path.size() << std::endl;    
    
    Json::Value member; 
    m_node = _node;               
           
    m_path.push_back(_node.getVarxName());
                
    member["decl"] = "Record";
    member["type"] = _node.getTypeName();
    member["name"] = _node.getVarxName();
    member["members"] = Json::Value();
        
    (*m_curr)[_node.getVarxName()] = member;
    
    m_curr = &((*m_curr)[_node.getVarxName()]["members"]);
    
    m_dept++;
    std::cout << "CDumpSerializerJson::addRecord():" << __LINE__ << " exit from .. m_path size = " << m_path.size() << std::endl;
}

bool 
CDumpSerializerJson::endRecord()
{   
    std::cout << "CDumpSerializerJson::endRecord():" << __LINE__ << " enter to .. m_path size = " << m_path.size() << std::endl;
    if (m_dept == 0) {
        return false;
    }
    
    m_dept--;
    m_curr = &m_root;
    m_path.pop_back();    
    if (m_path.size() <= 1) {
        
        std::cout << "CDumpSerializerJson::endRecord():" << __LINE__ << " exit from .. m_path size = " << m_path.size() << std::endl;
        
        return true;
    }
        
    m_curr = &m_root;
    for (unsigned int i = 1; i < m_path.size(); i++) {
        std::cout << "CDumpSerializerJson::endRecord():" << __LINE__ << " got name from path = " << m_path[i] << std::endl;
        m_curr = &((*m_curr)[m_path[i]]);
    }
    std::cout << "CDumpSerializerJson::endRecord():" << __LINE__ << " exit from .. m_path size = " << m_path.size() << std::endl;
    
    return true;
}

void
CDumpSerializerJson::close()
{
    std::ofstream   os;
    
    if (os.is_open()) {
        os.close();
    }
    os.open(m_name, std::ofstream::trunc);
    if ( ! os.is_open() ) {
        std::cout << "CDumpSerializerTest::serialize():" << __LINE__ << " failed open file " << m_name << std::endl;        
    }
        
    Json::StyledWriter sw;
    os << sw.write(m_root);
    os.close();    
}

