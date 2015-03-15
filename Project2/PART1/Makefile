CXX=g++
DEBUG=-g
CPPFLAGS=-Wall -c
LDFLAGS=-Wall
RM=rm -f
LDLIBS=-lstdc++

all: server-udp add-voter-udp vote-zero-udp vote-udp zeroize-udp list-candidates-udp vote-count-udp 

# Testing
test: test1
	./test1
	$(RM) test1

test1: test1.o
	$(CXX) $(LDFLAGS) -o test1 test1.o ../server.o $(LDLIBS)

# UDP functions
server-udp: server-udp.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o server-udp server-udp.cpp ../packetmaker.o ../server.o $(LDLIBS)

vote-zero-udp: vote-zero-udp.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o vote-zero-udp vote-zero-udp.cpp ../packetmaker.o ../server.o $(LDLIBS)

add-voter-udp: add-voter-udp.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o add-voter-udp add-voter-udp.cpp ../packetmaker.o ../server.o $(LDLIBS)

vote-udp: vote-udp.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o vote-udp vote-udp.cpp ../packetmaker.o ../server.o $(LDLIBS)

zeroize-udp: zeroize-udp.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o zeroize-udp zeroize-udp.cpp ../packetmaker.o ../server.o $(LDLIBS)

list-candidates-udp: list-candidates-udp.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o list-candidates-udp list-candidates-udp.cpp ../packetmaker.o ../server.o $(LDLIBS)

vote-count-udp: vote-count-udp.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o vote-count-udp vote-count-udp.cpp ../packetmaker.o ../server.o $(LDLIBS)

# Basic dependencies
../packetmaker.o: ../packetmaker.cpp ../packetmaker.h ../errorcode.h ../server.o

test1.o: test1.cpp ../server.o

../server.o: ../server.cpp ../server.h ../errorcode.h

# Clean up!
clean:
	$(RM) *.o *~ ../*.o ../*~ *-udp *.test
