#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/ptrace.h>
#include <vector>

#include "dump_process.h"
#include "dump_utils.h"

CDumpProcess::CDumpProcess() {
}

CDumpProcess::CDumpProcess(const CDumpProcess& orig) {
}

CDumpProcess::~CDumpProcess() {
}

bool 
CDumpProcess::parse(int _pid)
{
    std::ifstream       is;
    std::stringstream   ss;    
    
    ss << "/proc/" << _pid << "/maps";	
	is.open(ss.str().c_str());
    if ( ! is.is_open() ) {
        std::cout << "CDumpProcess::read(): ERROR - maps input stream '" << ss.str() << "' is not opened" << std::endl;
        
        return false;
    }
    
    if ( ! m_maps.parse(is) ) {
        std::cout << "CDumpProcess::read(): ERROR - while parsing '" << ss.str() << "'" << std::endl; 
        
        return false;
    }
    std::cout << "CDumpProcess::read(): read '" << ss.str() << "' is ok" << std::endl;
 
    return true;
}

bool 
CDumpProcess::attach(int _pid)
{
    long ptrace_result = ptrace(PTRACE_ATTACH, _pid, NULL, NULL);
    if (ptrace_result < 0) {
		std::cout << "CDumpProcess::attach(): error PTRACE attach pid " << _pid << std::endl;

        return false;
    }
	wait(NULL);
    std::cout << "CDumpProcess::attach(): PTRACE attach pid is ok" << _pid << std::endl;
    
    return true;
}

CDumpRegion *
CDumpProcess::search(dump::address_t _address)
{
    return m_maps.search(_address);
}

bool 
CDumpProcess::dettach(int _pid)
{
    ptrace(PTRACE_CONT, _pid, NULL, NULL);
    ptrace(PTRACE_DETACH, _pid, NULL, NULL);
    std::cout << "CDumpProcess::attach(): PTRACE dettach is ok" << std::endl;
    
    return true;
}