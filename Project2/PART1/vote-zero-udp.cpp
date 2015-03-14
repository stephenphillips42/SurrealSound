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

// Send packet and get response
string sendPacket(char* argv[], string packet);

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    cerr << "Usage: " << argv[0] << " host port..." << endl;
    exit(EXIT_FAILURE);
  }
  // Input handling
  ClientPacketMaker packetMaker(0);
  string packet = packetMaker.zeroize();

  string response = sendPacketUDP(argv[1],argv[2],packet);
  cout << packetMaker.parseresponse(response) << endl;

  exit(EXIT_SUCCESS);
}
