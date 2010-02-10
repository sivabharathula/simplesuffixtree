CC=g++
CFLAGS=-Wall -O2 
CXXFLAGS=-Wall -O2 -DBOOST_HAS_LONG_LONG -DNDEBUG 
OBJECTS=src/Example.o

default: all

all: suffixtree

LIBS = 

TARGET =	example

suffixtree:	$(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)
 

clean:
	rm -f $(OBJECTS) example

