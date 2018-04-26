#include <iosfwd>
#include <vector>

#include "dump_maps.h"
#include "dump_utils.h"
#include "dump_types.h"

CDumpMaps::CDumpMaps() {
}

CDumpMaps::CDumpMaps(const CDumpMaps &_from) 
{
    
}

CDumpMaps::~CDumpMaps() 
{    
    clear();
}

void 
CDumpMaps::clear()
{
    for (auto p_region : m_regions) {
        if (p_region != NULL) {
            delete p_region;
        }
    }
}

void 
CDumpMaps::add(CDumpRegion *_p_region)
{
    m_regions.push_back(_p_region);
}

bool
CDumpMaps::parse(std::ifstream &_is)
{
    if ( ! _is.is_open() ) {
        std::cout << "CDumpMaps::paese() stream is not open" << std::endl;
        
        return false;
    }
    
    int i = 0;
    std::string line;
    while (getline (_is,line) ) {
        std::cout << "CDumpProcess::read() line = " << line << std::endl;
        
        std::vector<std::string> fields;                        
        if (dump::split(line, ' ', fields) < 5) {
            std::cout << "CDumpProcess::read() ERROR - line is short '" << line << "'" << std::endl;
            
            return false;
        }
        CDumpRegion *p_region = new CDumpRegion();
        
        if ( ! p_region->parse(fields[0]) ) {
            std::cout << std::hex << "CDumpProcess::read() ERROR - parsing field '" << fields[0] << "' of line " << i << std::endl;
            
            return false;
        }           
        m_regions.push_back(p_region);    
        i++;
    }
    std::cout << "CDumpProcess::read() parse " << m_regions.size() << " lines of maps file" << std::endl;
    
    return true;
}

CDumpRegion *
CDumpMaps::search(const dump::address_t &_address)
{
    CDumpRegion *p_region = NULL;
    for (CDumpRegion *p_loop : m_regions) {
        if (p_loop == NULL) {
            std::cout << "CDumpMaps::search() got null region" << std::endl;
            
            return NULL;
        }
        
        if ( ! p_loop->inRange(_address) ) {
            continue;
        }
        std::cout << "CDumpMaps::search() found region '" << p_loop->toString() << "' in range of " << std::endl;
        p_region = p_loop;
    }
    
    return p_region;
}