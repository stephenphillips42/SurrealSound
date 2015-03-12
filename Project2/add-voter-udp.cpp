// This code from the man pages
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// C++ headers
#include <string>
#include <iostream>
// My headers
#include "packetmaker.h"

using namespace std;

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " host port voterid..." << endl;
    exit(EXIT_FAILURE);
  }
  // Input handling
  if (!isInteger(argv[3])) {
    cerr << "Voter ID must be an integer" << endl;
    exit(EXIT_FAILURE);
  }
  int voterid = atoi(argv[3]);

  // Get address matching intput arguments
  addrinfo hints;
  memset(&hints, 0, sizeof(addrinfo));
  hints.ai_family = AF_UNSPEC; // Allow IPv4 or IPv6
  hints.ai_socktype = SOCK_DGRAM; // Datagram socket
  hints.ai_flags = 0;
  hints.ai_protocol = 0; // Any protocol

  addrinfo *saddr;
  if (getaddrinfo(argv[1], argv[2], &hints, &saddr) < 0) {
    cerr << "Error with getaddrinfo" << endl;
    exit(EXIT_FAILURE);
  }
  if (saddr == NULL) {               // No address succeeded
    cerr << "Could not connect" << endl;
    exit(EXIT_FAILURE);
  }

  // So while getaddrinfo returns multiple, I just ignore all the other ones
  // return the first one.
  int ssocket =
        socket(saddr->ai_family, saddr->ai_socktype, saddr->ai_protocol);
  if (ssocket < 0) {
    cerr << "Failed to create socket to server" << endl;
    exit(EXIT_FAILURE);
  }
  if (connect(ssocket, saddr->ai_addr, saddr->ai_addrlen) < 0) {
    cerr << "Could not connect to server" << endl;
    exit(EXIT_FAILURE);
  }

  // Send remaining command-line arguments as separate
  // datagrams, and read responses from server
  ClientPacketMaker packetMaker(voterid);
  string packet = packetMaker.addvoter();
  cout << "Packet: " << packet << endl;
  if (write(ssocket, packet.c_str(), packet.size()+1)
        != (unsigned)(packet.size()+1)) {
    cerr << "Partial/failed write" << endl;
    exit(EXIT_FAILURE);
  }

  char buf[MAXLEN];
  ssize_t nread = read(ssocket, buf, MAXLEN);
  if (nread < 0) {
    perror("read");
    exit(EXIT_FAILURE);
  }
  // TODO: Parse message
  string s = "Hi there";
  cout << s.substr(s.size()) << endl;
  cout << packetMaker.parseresponse(string(buf)) << endl;


  exit(EXIT_SUCCESS);
}
