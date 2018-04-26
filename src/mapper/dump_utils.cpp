
#include "dump_utils.h"

#include <sstream>

namespace dump {
    
int 
split(const std::string &_s, char _delim, std::vector<std::string> &_v) {
    auto i = 0;
    auto pos = _s.find(_delim);
    
    _v.clear();
    while (pos != std::string::npos) {
      _v.push_back(_s.substr(i, pos-i));
      i = ++pos;
      pos = _s.find(_delim, pos);

      if (pos == std::string::npos)
         _v.push_back(_s.substr(i, _s.length()));
    }
    
    return _v.size();
}

std::string
toStringAddress(const dump::address_t &_address)
{
    std::stringstream ss;
    
    ss << _address.first << ":" << _address.second;
    
    return ss.str();
}   

std::string
toStringRange(const dump::range_t &_address)
{
    std::stringstream ss;
    
    ss << _address.first << "-" << _address.second;
    
    return ss.str();
}

}