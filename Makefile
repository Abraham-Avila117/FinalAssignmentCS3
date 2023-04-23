CC = clang++
PROGRAM = final
CFLAGS = -c
CPPFILES = FinalAssignment.cpp
# FILE = paths.txt

all: $(PROGRAM)

$(PROGRAM): FinalAssignment.o 
	$(CC) FinalAssignment.o -o $(PROGRAM)

FinalAssignment.o: $(CPPFILES)
	$(CC) $(CFLAGS) $(CPPFILES)

clean: 
	rm -f *.o

pclean:
	rm -f $(PROGRAM)
