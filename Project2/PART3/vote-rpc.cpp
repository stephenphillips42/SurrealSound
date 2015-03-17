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
#include "../packetmaker.h" // For isInteger
#include "rpc_server.h"
#include "rpc_errcode_util.h"

// Good old 'to string' implementation
#include <sstream>
#define SSTR( x ) ((dynamic_cast< std::ostringstream & > \
         ( std::ostringstream() << std::dec << x )).str()) 

using namespace std;

int
main(int argc, char *argv[])
{
  if (argc < 4) {
    cout << "Usage: " << argv[0] << " host candidate-name voterid..." << endl;
    exit(EXIT_FAILURE);
  }
  // Getting RPC connection
  CLIENT *cl;
  cl = clnt_create(argv[1], VOTESERVER, VOTESERVER_V1, "tcp");
  if (cl == NULL) {
    cout << "Error: Could not connect to RPC server" << endl;
    exit(EXIT_FAILURE);
  }
  // Input handling
  if (!isInteger(argv[3])) {
    cout << "Voter ID must be an integer" << endl;
    exit(EXIT_FAILURE);
  }
  // RPC Call
  NameIdPair arg;
  arg.voterid = atoi(argv[3]);
  arg.name = argv[2];
  RetVal *retval = rpc_votefor_1(&arg,cl);
  // RPC error checking
  if (retval == NULL) {
    cout << "Error: RPC call failed" << endl;
    exit(EXIT_FAILURE);
  }
  if (isError(retval->errcode)) {
    cout << "VOTEFOR: Error of type "
         << RPCErrCodeToString(retval->errcode) << endl;
  }
  else {
    cout << "VOTEFOR: Success of type: " 
         << RPCErrCodeToString(retval->errcode) << endl
         << "Return Value: " << retval->data << endl;
  }


  exit(EXIT_SUCCESS);
}
