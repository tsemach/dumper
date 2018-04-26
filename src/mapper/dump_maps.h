
#ifndef CDUMPMAPS_H
#define CDUMPMAPS_H

#include <list>
#include <iostream>
#include <fstream>

#include "dump_region.h"

class CDumpMaps {
public:
    CDumpMaps();
    CDumpMaps(const CDumpMaps &_from);
    virtual ~CDumpMaps();
    
    void clear();
    bool parse(std::ifstream &_is);    
    void add(CDumpRegion *_p_region);
    
    CDumpRegion *search(const dump::address_t &_address);
    
private:
    std::list<CDumpRegion *> m_regions;
};

#endif /* CDUMPMAPS_H */

