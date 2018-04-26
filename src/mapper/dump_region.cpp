
#include "dump_region.h"

#include <iostream>
#include <sstream>
#include  <iomanip>

#include "dump_utils.h"

using std::setw;
using std::setfill;
using std::hex;
        
CDumpRegion::CDumpRegion() 
{
    m_s_address = 0;
	m_e_address = 0;
}

CDumpRegion::CDumpRegion(const CDumpRegion &_from)
{
    m_s_address = _from.m_s_address;
    m_e_address = _from.m_e_address;
}

CDumpRegion::~CDumpRegion() 
{
}

CDumpRegion &
CDumpRegion::operator=(const CDumpRegion &_from)
{
    if (this == &_from) {
        return *this;
    }
    m_s_address = _from.m_s_address;
    m_e_address = _from.m_e_address;
    
    return *this;
}

void 
CDumpRegion::setStartAddress(unsigned long _s_address) 
{
		m_s_address = _s_address;
}

void 
CDumpRegion::setEndedAddress(unsigned long _e_address) 
{
	m_e_address = _e_address;
}
   
dump::u_long 
CDumpRegion::getSize() const
{
    return m_e_address - m_s_address;
}

std::string 
CDumpRegion::toString() const
{
    return dump::toStringRange(m_range);
}

bool 
CDumpRegion::inRange(dump::address_t _address) const
{
    // 1. check if _address.first (the address) is out of range
    if (_address.first < m_s_address || _address.first > m_e_address) {
        return false;
    }
    
    // 2. _address is in range now check it include all the size of the buffer
    if (_address.second > getSize()) {
        return false;
    }
    
    return true;
}

bool 
CDumpRegion::getBuffer(const dump::address_t &_address, dump::buffer_t &_buff)
{
    if ( ! inRange(_address) ) {
        std::cout << "CDumpRegion::getBuffer() _address - <" << dump::toStringAddress(_address) << "> is not in range" << std::endl;
        
        return false;
    }
    
    dump::u_long from = m_s_address + _address.first;
    _buff.clear();
    _buff.insert(_buff.end(), from, from + _address.second);
}

bool 
CDumpRegion::parse(const std::string &_range)
{
    std::vector<std::string>    v;
    std::stringstream           s1;
    std::stringstream           s2;            
                
    if (dump::split(_range, '-', v) < 2) {
        std::cout << "CDumpRegion::read() ERROR - range is too short '" << _range << "'" << std::endl;
            
        return false;
    }
     
    s1.str(v[0]);
    s1 >> std::hex >> m_s_address;
        
    s2.str(v[1]);
    s2 >> std::hex >> m_e_address;
    
    m_range.first = m_s_address;
    m_range.second = m_e_address;
    
    std::cout << std::hex << std::setw(v[0].length()) << std::setfill('0') << " CDumpRegion::read() v[0] = " << v[0] << ", s_address = " << m_s_address << std::endl;    
    std::cout << std::hex << std::setw(v[0].length()) << std::setfill('0') << " CDumpRegion::read() v[1] = " << v[1] << ", e_address = " << m_e_address << std::endl;        
    
    return true;
}

