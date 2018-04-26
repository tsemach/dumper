/* 
 * File:   CDumpSerializerStreamer.h
 * Author: tsemach
 *
 * Created on October 7, 2016, 10:01 PM
 */

#ifndef CDUMP_SERIALIZER_JSON_H
#define CDUMP_SERIALIZER_JSON_H

#include <fstream>
#include <vector>
#include <json/json.h>

#include "dump_serializer.h"
#include "dump_ast_node.h"

class CDumpSerializerJson : public CDumpSerializer {
public:
    CDumpSerializerJson();
    virtual ~CDumpSerializerJson();
        
    typedef std::vector<std::string> names_vector_t;
    
    virtual CDumpSerializerJson *clone();
    virtual bool open(const std::string &_name);
    virtual void close();
        
    virtual bool serialize(const CDumpASTNode &_node, u_int _value);
    virtual bool serialize(const CDumpASTNode &_node, char * _value);
    virtual bool serialize(const CDumpASTNode &_node, const std::string &_value);
    
    virtual bool addRecord(const CDumpASTNode &_node);
    virtual bool endRecord();
    
private:        
    std::string     m_name;    // the name of the top level class / filename to serialize.
    Json::Value     m_root;    // the json root node of class,     
    Json::Value    *m_curr;    // the curr node need to fill in case of complex structures like classes and structs     
    u_int           m_dept;    // store all names as appears, like ::[members][m_data][members][m_name] indicate class.m_data.m_name path.
    names_vector_t  m_path;    // store all names as appears, like ::[m_data][m_name] indicate class.m_data.m_name path.
    CDumpASTNode  m_node;    // the curr node is saved in case of handling complex types like record and structs.         
};

#endif /* CDUMP_SERIALIZER_JSON_H */

