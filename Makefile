CC=g++
CFLAGS=-c -g -Wall -rdynamic
LDFLAGS=-g -rdynamic

SOURCES=  \
PyJS.cpp \
pool_allocator.cpp \
PyJS_Threading.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: Script

Script: Script.o $(OBJECTS)
	$(CC) $(LDFLAGS) Script.o $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm Script Script.o $(OBJECTS)
