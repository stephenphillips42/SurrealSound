CXX=g++
DEBUG=-g
CPPFLAGS=-Wall -c
LDFLAGS=-Wall
RM=rm -f
LDLIBS=-lstdc++

all: part1

test: test1
	./test1

test1: test1.o
	$(CXX) $(LDFLAGS) -o test1 test1.o server.o $(LDLIBS)

part1.o: part1.cpp server.o

test1.o: test1.cpp server.o

server.o: server.cpp server.h

clean:
	$(RM) *.o *~ part1 test1
