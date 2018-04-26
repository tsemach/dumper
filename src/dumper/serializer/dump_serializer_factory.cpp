
#include "dump_serializer_factory.h"

#include "dump_serializer_common.h"

CDumpSerializerFactory::CDumpSerializerFactory()
{
    signeme(dump::serializer::serializer_type::e_json, &m_json);
}

CDumpSerializerFactory::~CDumpSerializerFactory()
{    
}
