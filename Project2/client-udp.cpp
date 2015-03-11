// This code from the man pages
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// C++ headers
#include <iostream>

using namespace std;

#define BUF_SIZE 512

int
main(int argc, char *argv[])
{

  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " host port msg..." << endl;
    exit(EXIT_FAILURE);
  }

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

  char buf[BUF_SIZE];
  for (int j = 3; j < argc; j++) {
    int len = strlen(argv[j]) + 1;
    // +1 for terminating null byte
    if (len + 1 > BUF_SIZE) {
      cerr << "Ignoring long message in argument " << j << endl;
      continue;
    }
    if (write(ssocket, argv[j], len) != len) {
      cerr << "Partial/failed write" << endl;
      exit(EXIT_FAILURE);
    }

    ssize_t nread = read(ssocket, buf, BUF_SIZE);
    if (nread < 0) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    cout << "Received " << nread << " bytes: " << buf << endl;
  }

  exit(EXIT_SUCCESS);
}
