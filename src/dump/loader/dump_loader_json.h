/* 
 * File:   CDumpLoaderStreamer.h
 * Author: tsemach
 *
 * Created on October 7, 2016, 10:01 PM
 */

#ifndef CDUMP_LOADER_JSON_H
#define CDUMP_LOADER_JSON_H

#include <fstream>
#include <json/json.h>

#include "dump_loader.h"

class CDumpLoaderJson : public CDumpLoader {
public:
    CDumpLoaderJson();
    virtual ~CDumpLoaderJson();
    
    virtual CDumpLoaderJson *clone();
    virtual bool open(const std::string &_name);
    virtual void close();
        
    virtual bool load(const std::string &_type, const std::string &_name, u_int &_value);
    virtual bool load(const std::string &_type, const std::string &_name, std::string &_value);
    
private:        
    Json::Value     m_root;    
};

#endif /* CDUMP_LOADER_JSON_H */

