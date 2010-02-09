CC=g++
CFLAGS=-Wall -g 
CXXFLAGS=-Wall -g -DBOOST_HAS_LONG_LONG -DNDEBUG 
OBJECTS=src/Node.o src/Edge.o src/NullEdge.o src/Suffix.o src/SuffixTree.o src/Example.o

default: all

all: suffixtree

LIBS = 

TARGET =	example

suffixtree:	$(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
 

clean:
	rm -f $(OBJECTS) example

