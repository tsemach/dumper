
#include <iostream>
#include <fstream>

#include "dump_serializer.h"

CDumpSerializer::CDumpSerializer(const std::string &_object_name)   
    : CDumpCommonObject(_object_name)
{
}

CDumpSerializer::~CDumpSerializer()
{
}

