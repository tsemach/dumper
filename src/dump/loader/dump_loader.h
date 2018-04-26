
#ifndef DUMP_LOADER_H
#define DUMP_LOADER_H

//#pragma once

#include <string>
#include "dump_common_object.h"

class CDumpLoader : public CDumpCommonObject<CDumpLoader> {
public:    
	CDumpLoader(const std::string &_object_name = std::string());
	virtual ~CDumpLoader();    

    //virtual CDumpLoader *clone() = 0; 
    virtual bool open(const std::string &_name) = 0;
    virtual void close() = 0;
    
    virtual bool load(const std::string &_type, const std::string &_name, u_int &_value) = 0;
    virtual bool load(const std::string &_type, const std::string &_name, std::string &_value) = 0;

private:   
};

#endif
