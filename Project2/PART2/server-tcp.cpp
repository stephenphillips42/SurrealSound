// Server code for electronic voting system
// Author: Stephen Phillips
// PennKey: stephi
// PennID: 14378269
#include "server.h"
#include "packetmaker.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// Network related things
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

void errorexit(const char *msg);
#define MAXSIZE 512
#define MAX_PENDING 10

// Run the server
int main(int argc, char *argv[]) {
  // General idea:
  // Create socket with port 8269 (datagram, INET?)
  // Use select to wait for something to come
  // When something does come, check the packet and process it accordingly
  cout << "Running server on localhost, port 8269" << endl;
  ServerPacketMaker packetMaker;

  // Get hint for the input address
  addrinfo hints;
  hints.ai_flags = AI_PASSIVE; // Whatever our current IP address is
  hints.ai_family = AF_UNSPEC; // IPv4 or IPv6, whatever it wants
  hints.ai_socktype = SOCK_STREAM; // We are using streams (TCP)
  hints.ai_protocol = 0; // Don't care about the protocol
  hints.ai_addrlen = 0; // Don't care about any of these
  hints.ai_addr = NULL;
  hints.ai_canonname = NULL;
  hints.ai_next = NULL;
  // Get our IP address
  addrinfo *serveraddr;
  if (getaddrinfo(NULL,"8269",&hints,&serveraddr) < 0) {
    perror("Unable to get own IP address");
    exit(EXIT_FAILURE);
  }

  // OK so technically this returns a list - I'll ignore them and just use
  // the first one returned
  // Set up the socket
  int ssocket = 0; // Server Socket
  if ((ssocket = socket(PF_INET,SOCK_STREAM,0)) < 0) {
    perror("Socket unable to connect");
    exit(EXIT_FAILURE);
  }
  // Now get IP address and such
  if((bind(ssocket, serveraddr->ai_addr, serveraddr->ai_addrlen))<0) {
    perror("Socket unable to bind");
    exit(EXIT_FAILURE);
  }
  // Main loop
  // Connections can be pending if many concurrent client requests
  listen(ssocket, MAX_PENDING);
  // How many bytes we received
  int nbytes = 0;
  // Client address information
  int csocket = 0; // Client socket
  sockaddr_storage clientaddr;
  socklen_t addrlen = 0;
  // Client message
  char msg[MAXSIZE];
  string response;
  while(true) { // Loop forever...
    // Wait for a message
    if((csocket = accept(ssocket, (sockaddr*)&clientaddr, &addrlen)) <0) {
      errorexit("Error with accepting");
    }

    // Guaranteed for all messages that we only get 1 packet-worth of data
    if ((nbytes = read(csocket, msg, sizeof(msg))) < 0) {
      errorexit("Trouble receiving data");
    }

    // Echo the input
    cout << "Got message: " << msg << endl;

    // Respond to the sender.
    response = packetMaker.processpacket(msg);
    nbytes = response.size()+1;
    cerr << "Sending response: " << response << endl;
    // Write data out (write = send with no flags)
    if (write(csocket, response.c_str(), nbytes) != nbytes) {
      errorexit("Trouble sending data");
    }
    cerr << "Closing connection with client ..." << endl;
    close(csocket);
    cerr << "------- Done -------" << endl << endl;
  }

  close(ssocket);
}

void errorexit(const char *msg) {
  perror (msg);
  exit (EXIT_FAILURE);
}
