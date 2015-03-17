CXX=g++
DEBUG=-g
CPPFLAGS=-Wall -c
LDFLAGS=-Wall
RM=rm -f
LDLIBS=-lstdc++

all: server-nb add-voter-nb vote-zero-nb vote-nb list-candidates-nb vote-count-nb

# TCP functions
server-nb: server-nb.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o server-nb server-nb.cpp ../packetmaker.o ../server.o $(LDLIBS)

vote-zero-nb: vote-zero-nb.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o vote-zero-nb vote-zero-nb.cpp ../packetmaker.o ../server.o $(LDLIBS)

add-voter-nb: add-voter-nb.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o add-voter-nb add-voter-nb.cpp ../packetmaker.o ../server.o $(LDLIBS)

vote-nb: vote-nb.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o vote-nb vote-nb.cpp ../packetmaker.o ../server.o $(LDLIBS)

list-candidates-nb: list-candidates-nb.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o list-candidates-nb list-candidates-nb.cpp ../packetmaker.o ../server.o $(LDLIBS)

vote-count-nb: vote-count-nb.cpp ../packetmaker.o ../server.o
	$(CXX) $(LDFLAGS) -o vote-count-nb vote-count-nb.cpp ../packetmaker.o ../server.o $(LDLIBS)


# Basic dependencies
../packetmaker.o: ../packetmaker.cpp ../packetmaker.h ../errorcode.h ../server.o

../server.o: ../server.cpp ../server.h ../errorcode.h

# Clean up!
clean:
	$(RM) *.o *~ *-nb
