/* 
 * File:   dump_loader_test.h
 * Author: tsemach
 *
 * Created on October 7, 2016, 3:58 PM
 */

#ifndef DUMP_LOADER_TEST_H
#define DUMP_LOADER_TEST_H

#include <fstream>
#include <json/json.h>
#include <json/writer.h>

#include "dump_loader.h"
#include "dump_loader_factory.h"
#include "dump_loader_common.h"

class CDumpLoaderTest {
public:
    CDumpLoaderTest();
    virtual ~CDumpLoaderTest();
    
    template <typename T>
	bool load(T &_class, const std::string &_filename) {
        std::cout << "CDumpLoaderTest::serialize():" << __LINE__ << " enter to serialize" << std::endl;
        
        CDumpLoader *p_loader = m_factory.get(dump::loader::loader_type::e_json);
        if ( ! p_loader ) {
            std::cout << "CDumpLoaderTest::serialize():" << __LINE__ << " got null loader" << std::endl;
            
            return false;
        }  
        
        if ( ! p_loader->open(_filename) ) {
            std::cout << "CDumpLoaderTest::serialize():" << __LINE__ << " failed open file " << _filename << std::endl;
            
            return false;
        }
        
        if ( ! p_loader->load(std::string("std::string"), std::string("m_name"), _class.m_name) ) {
            std::cout << "CDumpLoaderTest::serialize():" << __LINE__ << " failed serialize m_name" << _filename << std::endl;
        
            return false;
        }
        
        std::cout << "CDumpLoaderTest::serialize():" << __LINE__ << " going to serialize m_id = " << _class.m_id << std::endl;
        if ( ! p_loader->load(std::string("std::string"), std::string("m_name"), _class.m_id) ) {
            std::cout << "CDumpLoaderTest::serialize():" << __LINE__ << " failed serialize m_name" << _filename << std::endl;
        
            return false;
        }
        
        if ( ! p_loader->load(std::string("u_int"), std::string("m_name"), _class.m_id) ) {
            std::cout << "CDumpLoaderTest::serialize():" << __LINE__ << " failed serialize m_name" << _filename << std::endl;
        
            return false;
        }
        std::cout << "CDumpLoaderTest::serialize():" << __LINE__ << " end of serialize" << std::endl;
        
        p_loader->close();
    
        return true;
    }
    
private:    
    CDumpLoaderFactory    m_factory;
};

#endif /* DUMP_LOADER_TEST_H */

