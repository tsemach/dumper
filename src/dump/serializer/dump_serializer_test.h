/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dump_serializer_test.h
 * Author: tsemach
 *
 * Created on October 7, 2016, 3:58 PM
 */

#ifndef DUMP_SERIALIZER_TEST_H
#define DUMP_SERIALIZER_TEST_H

#include <fstream>
#include <json/json.h>
#include <json/writer.h>

#include "dump_serializer.h"
#include "dump_serializer_factory.h"
#include "dump_serializer_common.h"

class CDumpSerializerTest {
public:
    CDumpSerializerTest();           
    virtual ~CDumpSerializerTest();
    
    template <typename T>
	bool dump(T &_class, const std::string &_filename) {
        std::cout << "CDumpSerializerTest::dump():" << __LINE__ << " enter to serialize" << std::endl;
        
        CDumpSerializer *p_serializer = m_factory.get(dump::serializer::serializer_type::e_json);
        if ( ! p_serializer ) {
            std::cout << "CDumpSerializerTest::dump():" << __LINE__ << " got null serializer" << std::endl;
            
            return false;
        }
        //CDumpSerializerStreamer *p_streamer = m_factory.get(streamer_type::e_json);
        //CDumpSerializer serializer = CDumpSerializerFactory::instance().get(streamer_type::e_json);
        
        if ( ! p_serializer->open(_filename) ) {
            std::cout << "CDumpSerializerTest::dump():" << __LINE__ << " failed open file " << _filename << std::endl;
            
            return false;
        }                       
        
        CDumpASTNode _node;
        
        _node.setTypeName("std::string");
        _node.setVarxName("m_name");        
        if ( ! p_serializer->serialize(_node, _class.m_name) ) {
            std::cout << "CDumpSerializerTest::dump():" << __LINE__ << " end of serialize on m_name" << std::endl;
            
            return false;
        }
        
        _node.setTypeName("std::string");
        _node.setVarxName("m_id");
        if ( ! p_serializer->serialize(_node, (u_int)_class.m_id) ) {
            std::cout << "CDumpSerializerTest::dump():" << __LINE__ << " end of serialize on m_id" << std::endl;
            
            return false;            
        }
                
        std::cout << "CDumpSerializerTest::dump() going to serialize m_data (CData class)" << std::endl;
        
        // add CData class of CTest
        _node.setTypeName("pCData");
        _node.setVarxName("m_data");
        p_serializer->addRecord(_node);        
        std::cout << "CDumpSerializerTest::dump() after add record (CData class)" << std::endl;
        
        _node.setTypeName("pchar");
        _node.setVarxName("m_buff");  
        std::cout << "CDumpSerializerTest::dump(char *):" << __LINE__ << " before calling to serialize _class.m_data->m_buff = " << _class.m_data->m_buff << std::endl;
        p_serializer->serialize(_node, _class.m_data->m_buff);
                
        _node.setTypeName("size_t");
        _node.setVarxName("m_size");       
        p_serializer->serialize(_node,_class.m_data->m_size);                
        
        {
            // add CMore class of CData
            _node.setTypeName("CMore");
            _node.setVarxName("m_more");
            p_serializer->addRecord(_node);        

            _node.setTypeName("int");
            _node.setVarxName("m_cmore_size");       
            p_serializer->serialize(_node,_class.m_data->m_more.m_cmore_size);

            _node.setTypeName("std::string");
            _node.setVarxName("m_cmore_name");       
            p_serializer->serialize(_node,_class.m_data->m_more.m_cmore_name);

            p_serializer->endRecord();
            // end of CMore class of CData
        }
        
        p_serializer->endRecord();
        std::cout << "CDumpSerializerTest::dump() after serialize pchar (CData class)" << std::endl;
        // end of CData class
        
        std::cout << "CDumpSerializerTest::dump():" << __LINE__ << " end of serialize" << std::endl;
        
        p_serializer->close();
    
        return true;
    }
    
private:    
    CDumpSerializerFactory    m_factory;
};

#endif /* DUMP_SERIALIZER_TEST_H */

