PROGS = prog1 prog2
SRCDIR = .
SRCFILES = $(addprefix $(SRCDIR)/, $(PROGS))
CPPFILES = $(addsuffix .cpp, $(SRCFILES))
HPPFILES = $(addsuffix .h, $(SRCFILES))
OBJFILES = $(patsubst %.cpp,%.o, $(CPPFILES))

CC=g++
CCFLAGS=-std=c++11 -I.
CPPFLAGS = $(CCFLAGS)

%.o: %.cpp %.h	
	$(CC) -c -std=c++11 $(filter %.cpp,$<) -o $@ $(CCFLAGS)

$(PROGS): $(OBJFILES)
	$(CC) -Wmultichar -std=c++11 $< -o $@ $(CCFLAGS)

clean:
	@rm -f *.o
	@rm -f $(PROGS)
