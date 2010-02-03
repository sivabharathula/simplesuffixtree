CC=g++
CFLAGS=-Wall
OBJECTS=Node.o Edge.o Suffix.o SuffixTree.o Example.o

default: all

all: suffixtree

.cpp.o:
	$(CC) $(CFLAGS) -c $<

suffixtree: $(OBJECTS)
	$(CC) $(OBJECTS) -o example

clean:
	rm -f Node.o Edge.o Suffix.o SuffixTree.o Example.o example

