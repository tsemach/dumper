PROG=dump
CFILES =  dump_dummy.cpp dump_utils.cpp dump_test.cpp dump_region.cpp dump_maps.cpp dump_process.cpp dump.cpp 
HFILES = dump_utils.h dump_test.h dump_region.h dump_maps.h dump_process.h
OFILES = $(patsubst %.cpp,%.o, $(CFILES))
CC=g++
CCFLAGS=-std=c++11 -I.
CPPFLAGS = $(CCFLAGS)

#all: dump_entry dump_maps dump_process dump check
all: dump check serializer

%.o: %.cpp %.h	
	$(CC) -c -std=c++11 $(filter %.cpp,$<) -o $@ $(CCFLAGS)

#dump_utils.o: dump_utils.cpp
#	$(CC) -c -std=c++11 dump_utils.cpp -o dump_utils.o $(CCFLAGS)
		
#dump_maps.o: dump_maps.cpp
#	$(CC) -c -std=c++11 $< -o $@ $(CCFLAGS)

#dump_process.o: dump_process.cpp
#	$(CC) -c -std=c++11 $< -o $@ $(CCFLAGS)

dump.o: dump.cpp
	$(CC) -c -std=c++11 $< -o $@ $(CCFLAGS)
	
$(PROG): $(OFILES)
	$(CC) -std=c++11 $< $(OFILES) -o $@ $(CCFLAGS)

check: check.cpp dump_test.cpp
	$(CC) -Wmultichar -std=c++11 $^ -o $@ $(CCFLAGS)

serializer: serializer.cpp
	$(CC) -Wmultichar -std=c++11 $< -o $@ $(CCFLAGS)
	
clean:
	@rm -f *.o
	@rm -f $(PROG)
	@rm -f check	
	@rm -f serializer
