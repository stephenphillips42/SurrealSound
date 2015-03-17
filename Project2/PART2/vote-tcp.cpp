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
  if (argc < 5) {
    cout << "Usage: " << argv[0] << " host port candidate-name voterid..." << endl;
    exit(EXIT_FAILURE);
  }
  // Input handling
  if (!isInteger(argv[4])) {
    cout << "Voter ID must be an integer" << endl;
    exit(EXIT_FAILURE);
  }
  int voterid = atoi(argv[4]);
  string name(argv[3]);
  ClientPacketMaker packetMaker(voterid);
  string packet = packetMaker.votefor(name);

  string response = sendPacketTCP(argv[1],argv[2],packet);
  cout << packetMaker.parseresponse(response) << endl;

  exit(EXIT_SUCCESS);
}
