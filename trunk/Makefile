CC=g++
CFLAGS=-Wall
OBJECTS=src/Node.o src/Edge.o src/Suffix.o src/SuffixTree.o src/Example.o

default: all

all: suffixtree

LIBS = 

TARGET =	example

suffixtree:	$(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)
 

clean:
	rm -f $(OBJECTS) example

