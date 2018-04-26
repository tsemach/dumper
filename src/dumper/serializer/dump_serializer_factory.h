/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dump_serializer_factory.h
 * Author: tsemach
 *
 * Created on October 7, 2016, 9:34 PM
 */

#ifndef DUMP_SERIALIZER_STREAMER_FACTORY_H
#define DUMP_SERIALIZER_STREAMER_FACTORY_H

#include "dump_common_factory.h"
#include "dump_serializer_common.h"
#include "dump_serializer_json.h"

using namespace dump::serializer;

class CDumpSerializerFactory : public CDumpCommonFacory<serializer_type, CDumpSerializer>  {
public:    
    CDumpSerializerFactory(); 
    virtual ~CDumpSerializerFactory();

private:
    CDumpSerializerJson   m_json;
};

#endif 

