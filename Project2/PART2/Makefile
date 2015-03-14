CXX=g++
DEBUG=-g
CPPFLAGS=-Wall -c
LDFLAGS=-Wall
RM=rm -f
LDLIBS=-lstdc++

all: server-tcp add-voter-tcp vote-zero-tcp vote-tcp zeroize-tcp list-candidates-tcp vote-count-tcp

# TCP functions
server-tcp: server-tcp.cpp packetmaker.o server.o
	$(CXX) $(LDFLAGS) -o server-tcp server-tcp.cpp packetmaker.o server.o $(LDLIBS)

vote-zero-tcp: vote-zero-tcp.cpp packetmaker.o server.o
	$(CXX) $(LDFLAGS) -o vote-zero-tcp vote-zero-tcp.cpp packetmaker.o server.o $(LDLIBS)

add-voter-tcp: add-voter-tcp.cpp packetmaker.o server.o
	$(CXX) $(LDFLAGS) -o add-voter-tcp add-voter-tcp.cpp packetmaker.o server.o $(LDLIBS)

vote-tcp: vote-tcp.cpp packetmaker.o server.o
	$(CXX) $(LDFLAGS) -o vote-tcp vote-tcp.cpp packetmaker.o server.o $(LDLIBS)

zeroize-tcp: zeroize-tcp.cpp packetmaker.o server.o
	$(CXX) $(LDFLAGS) -o zeroize-tcp zeroize-tcp.cpp packetmaker.o server.o $(LDLIBS)

list-candidates-tcp: list-candidates-tcp.cpp packetmaker.o server.o
	$(CXX) $(LDFLAGS) -o list-candidates-tcp list-candidates-tcp.cpp packetmaker.o server.o $(LDLIBS)

vote-count-tcp: vote-count-tcp.cpp packetmaker.o server.o
	$(CXX) $(LDFLAGS) -o vote-count-tcp vote-count-tcp.cpp packetmaker.o server.o $(LDLIBS)


# Basic dependencies
packetmaker.o: packetmaker.cpp packetmaker.h errorcode.h server.o

test1.o: test1.cpp server.o

server.o: server.cpp server.h errorcode.h

# Clean up!
clean:
	$(RM) *.o *~ server-udp test1 *-udp *-tcp *.test
