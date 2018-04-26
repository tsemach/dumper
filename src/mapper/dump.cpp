
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <string>
#include <ostream>
#include <iostream>
#include <utility>
#include <iomanip>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/ptrace.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "dump_region.h"
#include "dump_maps.h"
#include "dump_process.h"

//------------------------------------------------------------------------------------------------------------
template<class L, class R>
class CMine {
public:
	CMine(L _l, R _r) : l(_l), r(_r) {
		std::cout << "CMine: (t,r) = (" << l << "," << r << ")" << std::endl;
	}
	
	bool operator()() {
		return l == r;
	}
private:
	L l;
	R r;
};

template<typename T1, typename T2>
auto Plus1(T1&& t1, T2&& t2) -> decltype(std::forward<T1>(t1) + std::forward<T2>(t2))
{
	CMine<T1, T2> my(t1, t2);

	
	//return std::forward<T1>(t1) + std::forward<T2>(t2);
	return my();
}

template<typename T1, typename T2>
bool 
Plus2(T1 t1, T2 t2) 
{
	CMine<T1, T2> my(t1, t2);

	
	return my();
}


int 
factorial1(int n) 
{
	int f = 1;

	for (int i = 1; i <= n; i++) {
		f = f * i;
		std::cout << "f  = " << f << " i = " << i <<  std::endl;
	}

	return f;
}

int 
factorial2(int n) 
{
	
	if (n <= 1) { 
		return 1;
	}
	
	return factorial2(n - 1) * n;
}

void
autoTest()
{
	std::cout << factorial1(4) << std::endl;	
	std::cout << factorial2(4) << std::endl;	
	int n = 8;
	int w = n >> 2;

	std::cout << "w = " << w << " n = " << n << std::endl;

	std::cout << "main: etnter to .." << std::endl;
	std::cout << "plus1(5,6) = " << Plus1(5,6) << std::endl;
	std::cout << "plus2(5,6) = " << Plus2(5,6) << std::endl;
	std::cout << "plus2(5,5) = " << Plus2(5,5) << std::endl;

	CMine<int, int> my(5, 6);
	auto i = 6;

}
//------------------------------------------------------------------------------------------------------------

class CTest {
public:
	CTest() : m_number(0) {}
   ~CTest() {}

	void print() {
		std::cout << "CTest::print() m_name = " << m_name << std::endl;
		std::cout << "CTest::print() m_number = " << m_number << std::endl;
	}

	void set(int i) { 
		m_number = i;
	}
	
	void name(const std::string &_name) {
		m_name = _name;	
	}		

private:
	std::string m_name;
	int m_number;
};

int
checkClass()
{
	//autoTest();
	
	pid_t p = getpid();
	std::cout << "main: pid = " << p << std::endl;

	CTest t;
	
	std::cout << "main: size of t = " << sizeof(t) << std::endl;
	std::cout << "main: size of CTest = " << sizeof(CTest) << std::endl;

	void *p_void = new char[sizeof(CTest)];	
	CTest *p_t = (CTest *)p_void;

	p_t->set(64);
	p_t->name("TSEMACH");
	p_t->print();	

	sleep(1000);	
}

void 
dump_memory_region(FILE* pMemFile, unsigned long start_address, long length, int serverSocket)
{
    unsigned long address;
    int pageLength = 4096;
    unsigned char page[pageLength];
    fseeko(pMemFile, start_address, SEEK_SET);

    for (address=start_address; address < start_address + length; address += pageLength)
    {
        fread(&page, 1, pageLength, pMemFile);
        if (serverSocket == -1)
        {
            // write to stdout
            fwrite(&page, 1, pageLength, stdout);
        }
        else
        {
            send(serverSocket, &page, pageLength, 0);
        }
    }
}

void 
dump_region(FILE* pMemFile, unsigned long start_address, long length, int serverSocket)
{
    unsigned long address;
    int pageLength = 4096;
    unsigned char page[pageLength];
    fseeko(pMemFile, start_address, SEEK_SET);

    for (address=start_address; address < start_address + length; address += pageLength)
    {
        fread(&page, 1, pageLength, pMemFile);
        if (serverSocket == -1)
        {
            // write to stdout
            fwrite(&page, 1, pageLength, stdout);
        }
        else
        {
            send(serverSocket, &page, pageLength, 0);
        }
    }
}

bool
parse_maps(int _pid) 
{	
    CDumpProcess    process;
    
    process.attach(_pid);
    process.parse(_pid);
    
    CDumpRegion *p_region = process.search(dump::address_t((dump::u_long)0x6032a0, 40));
    
    if ( ! p_region ) {
        std::cout << "::parse_maps() ERROR - region is null" << std::endl;
    }
    
    dump::buffer_t buff;
    
    if ( ! p_region->getBuffer(dump::address_t((dump::u_long)0x6032a0, 40), buff) ) {
        std::cout << "::parse_maps() ERROR - while getting buffer" << std::endl;                
    }
    
    process.dettach(_pid);
}

#if 0
bool
dump(int _pid) 
{	
	long ptrace_result = ptrace(PTRACE_ATTACH, _pid, NULL, NULL);
    if (ptrace_result < 0) {
		std::cout << "main: error PTRACE attach pid " << _pid << std:endl;

        return false;
    }
	wait(NULL);

	std::stringstream ss;

	ss << "/proc/" << _pid << "/maps";

	std::ifstream is;

	is.open(ss.str(), std::ios::in | std::ios::binary);
	char mapsFilename[1024];

        sprintf(mapsFilename, "/proc/%s/maps", argv[1]);

        //sprintf(mapsFilename, "/proc/self/maps", argv[1]);
        FILE* pMapsFile = fopen(mapsFilename, "r");
        char memFilename[1024];
        sprintf(memFilename, "/proc/%s/mem", argv[1]);
        FILE* pMemFile = fopen(memFilename, "r");
        int serverSocket = -1;

        char line[256];
        while (fgets(line, 256, pMapsFile) != NULL)
        {
            unsigned long start_address;
            unsigned long end_address;
            sscanf(line, "%08lx-%08lx\n", &start_address, &end_address);
            dump_memory_region(pMemFile, start_address, end_address - start_address, serverSocket);
        }
        fclose(pMapsFile);
        fclose(pMemFile);
        if (serverSocket != -1)
        {
            close(serverSocket);
        }

        ptrace(PTRACE_CONT, pid, NULL, NULL);
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
    }
    else
    {
        printf("%s <pid>\n", argv[0]);
        printf("%s <pid> <ip-address> <port>\n", argv[0]);
        exit(0);
    }
}
#endif

int
main(int argc, char **argv) 
{
	//checkClass();
    parse_maps(atoi(argv[1]));
    
    return 0;
#if 0    
    if (argc == 2 || argc == 4)
    {
        int pid = atoi(argv[1]);
        long ptraceResult = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
        if (ptraceResult < 0) {
            printf("Unable to attach to the pid specified\n");

            return -1;
        }
        wait(NULL);

        char mapsFilename[1024];
        sprintf(mapsFilename, "/proc/%s/maps", argv[1]);
        //sprintf(mapsFilename, "/proc/self/maps", argv[1]);
        FILE* pMapsFile = fopen(mapsFilename, "r");
        char memFilename[1024];
        sprintf(memFilename, "/proc/%s/mem", argv[1]);
        FILE* pMemFile = fopen(memFilename, "r");
        int serverSocket = -1;
        if (argc == 4)
        {   
            unsigned int port;
            int count = sscanf(argv[3], "%d", &port);
            if (count == 0)
            {
                printf("Invalid port specified\n");
                return -1;
            }
            serverSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (serverSocket == -1)
            {
                printf("Could not create socket\n");
                return -1;
            }
            struct sockaddr_in serverSocketAddress;
            serverSocketAddress.sin_addr.s_addr = inet_addr(argv[2]);
            serverSocketAddress.sin_family = AF_INET;
            serverSocketAddress.sin_port = htons(port);
            if (connect(serverSocket, (struct sockaddr *) &serverSocketAddress, sizeof(serverSocketAddress)) < 0)
            {
                printf("Could not connect to server\n");
                return -1;
            }
        }
        char line[256];
        while (fgets(line, 256, pMapsFile) != NULL)
        {
            unsigned long start_address;
            unsigned long end_address;
            sscanf(line, "%08lx-%08lx\n", &start_address, &end_address);
            dump_memory_region(pMemFile, start_address, end_address - start_address, serverSocket);
        }
        fclose(pMapsFile);
        fclose(pMemFile);
        if (serverSocket != -1)
        {
            close(serverSocket);
        }

        ptrace(PTRACE_CONT, pid, NULL, NULL);
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
    }
    else
    {
        printf("%s <pid>\n", argv[0]);
        printf("%s <pid> <ip-address> <port>\n", argv[0]);
        exit(0);
    }
#endif    
}
