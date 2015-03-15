CXX=g++
DEBUG=-g
CPPFLAGS=-Wall -c
LDFLAGS=-Wall
RM=rm -f
LDLIBS=-lstdc++

all: server-rpc add-voter-rpc vote-zero-rpc vote-rpc list-candidates-rpc vote-count-rpc

# Making the RPC service
server-rpc: rpc_server_svc.o rpc_server_xdr.o server_rpc_impl.o ../server.o
	$(CXX) $(LDFLAGS) -o server-rpc rpc_server_svc.o rpc_server_xdr.o server_rpc_impl.o ../server.o

add-voter-rpc: add-voter-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o
	$(CXX) $(LDFLAGS) -o add-voter-rpc add-voter-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o

vote-zero-rpc: vote-zero-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o
	$(CXX) $(LDFLAGS) -o vote-zero-rpc vote-zero-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o

vote-rpc: vote-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o
	$(CXX) $(LDFLAGS) -o vote-rpc vote-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o

list-candidates-rpc: list-candidates-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o
	$(CXX) $(LDFLAGS) -o list-candidates-rpc list-candidates-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o

vote-count-rpc: vote-count-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o
	$(CXX) $(LDFLAGS) -o vote-count-rpc vote-count-rpc.o rpc_server_xdr.o rpc_server_clnt.o ../server.o ../packetmaker.o

# Basic dependencies
../packetmaker.o: ../packetmaker.cpp ../packetmaker.h ../errorcode.h ../server.o

../server.o: ../server.cpp ../server.h ../errorcode.h

# Clean up!
clean:
	$(RM) *.o *~ *-rpc
