CXX=g++
DEBUG=-g
CPPFLAGS=-Wall -c
LDFLAGS=-Wall
RM=rm -f
LDLIBS=-lstdc++

all: server-udp client-udp

test: test1
	./test1
	$(RM) test1

test1: test1.o
	$(CXX) $(LDFLAGS) -o test1 test1.o server.o $(LDLIBS)

client-udp.o: client-udp.cpp

server-udp.o: server-udp.cpp server.o

test1.o: test1.cpp server.o

server.o: server.cpp server.h

clean:
	$(RM) *.o *~ server-udp test1 client-udp
