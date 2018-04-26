/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dump_loader_factory.h
 * Author: tsemach
 *
 * Created on October 7, 2016, 9:34 PM
 */

#ifndef DUMP_LOADER_STREAMER_FACTORY_H
#define DUMP_LOADER_STREAMER_FACTORY_H

#include "dump_common_factory.h"
#include "dump_loader_common.h"
#include "dump_loader_json.h"

using namespace dump::loader;

class CDumpLoaderFactory : public CDumpCommonFacory<loader_type, CDumpLoader>  {
public:    
    CDumpLoaderFactory(); 
    virtual ~CDumpLoaderFactory();
private:
    CDumpLoaderJson   m_json;
};

#endif 

