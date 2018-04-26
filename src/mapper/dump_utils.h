
#ifndef DUMP_UTILS_H
#define DUMP_UTILS_H

#include <string>
#include <vector>

#include "dump_types.h"
namespace dump {

int 
split(const std::string &_s, char _delim, std::vector<std::string> &_v);

std::string
toStringAddress(const dump::address_t &_address);

std::string
toStringRange(const dump::range_t &_range);

}

#endif /* DUMP_UTILS_H */

