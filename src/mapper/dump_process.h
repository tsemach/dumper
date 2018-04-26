
#ifndef CDUMPPROCESS_H
#define CDUMPPROCESS_H

#include "dump_types.h"
#include "dump_maps.h"

class CDumpProcess {
public:
    CDumpProcess();
    CDumpProcess(const CDumpProcess& orig);
    virtual ~CDumpProcess();
    
    bool parse(int _pid);    
    bool attach(int _pid);
    bool dettach(int _pid);
    
    CDumpRegion *search(dump::address_t _address);
    
private:
    CDumpMaps   m_maps;
};

#endif /* CDUMPPROCESS_H */

