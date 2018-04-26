
#ifndef DUMP_SERIALIZER_H
#define DUMP_SERIALIZER_H

//#pragma once

#include <string>

#include "dump_ast_node.h"
#include "dump_common_object.h"

class CDumpSerializer : public CDumpCommonObject<CDumpSerializer> {
public:    
	CDumpSerializer(const std::string &_object_name = std::string());
	virtual ~CDumpSerializer();    

    //virtual CDumpSerializer *clone() = 0; 
    virtual bool open(const std::string &_name) = 0;
    virtual void close() = 0;
    
    virtual bool serialize(const CDumpASTNode &_node, u_int _value) = 0;
    virtual bool serialize(const CDumpASTNode &_node, char * _value) = 0;
    virtual bool serialize(const CDumpASTNode &_node, const std::string &_value) = 0;

    virtual bool addRecord(const CDumpASTNode &_node) = 0;
    virtual bool endRecord() = 0;
    
private:   
};

#endif
