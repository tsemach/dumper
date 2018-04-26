
#ifndef DUMP_TYPES_H
#define DUMP_TYPES_H

#include <vector>

namespace dump {
    
typedef unsigned long               u_long;
typedef unsigned char               u_char;
typedef std::pair<u_long, u_long>   address_t;
typedef std::pair<u_long, u_long>   range_t;
typedef std::vector<u_char>         buffer_t;

}

#endif /* DUMP_TYPES_H */

