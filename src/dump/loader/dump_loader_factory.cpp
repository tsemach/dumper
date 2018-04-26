
#include "dump_loader_factory.h"

#include "dump_loader_common.h"

CDumpLoaderFactory::CDumpLoaderFactory()
{
    signeme(dump::loader::loader_type::e_json, &m_json);
}

CDumpLoaderFactory::~CDumpLoaderFactory()
{    
}
