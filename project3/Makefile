CC = gcc
CCFLAGS = -Wall -g
OBJ = project3.o objdb.o

prog: $(OBJ)
	$(CC) $(OBJ) -o project3

objdb.o: objdb.c objdb.h
	$(CC) $(CCFLAGS) -c $<

project3.0: project3.c objdb.h
	$(CC) $(CCFLAGS) -c $<

.PHONY: clean
clean:
	rm -f*.o 
