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
#include "../packetmaker.h"

using namespace std;

int
main(int argc, char *argv[])
{
  if (argc < 4) {
    cout << "Usage: " << argv[0] << " host port candidate-name..." << endl;
    exit(EXIT_FAILURE);
  }
  // Input handling
  string name(argv[3]);
  ClientPacketMaker packetMaker(0);
  string packet = packetMaker.votecount(name);

  string response = sendPacketTCP(argv[1],argv[2],packet);
  cout << packetMaker.parseresponse(response) << endl;

  exit(EXIT_SUCCESS);
}
