#ifndef __PROCESS_DUMP_H
#define __PROCESS_DUMP_H

#include <string>

#include "dump_types.h"

class CDumpRegion {	
public:	
	CDumpRegion();
    CDumpRegion(const CDumpRegion &_from);
   ~CDumpRegion();
	    
    CDumpRegion &operator=(const CDumpRegion &_from);
    
    bool parse(const std::string &_range);
    
	void setStartAddress(unsigned long _s_address);
	void setEndedAddress(unsigned long _e_address);
	
    dump::u_long getSize() const;
    bool getBuffer(const dump::address_t &_address, dump::buffer_t &_buff);
    bool inRange(dump::address_t _address) const;
    
    
    std::string toString() const;
    
private:
    dump::range_t   m_range;
	unsigned long   m_s_address;
	unsigned long   m_e_address;
};

#endif /* __PROCESS_DUMP_H */

