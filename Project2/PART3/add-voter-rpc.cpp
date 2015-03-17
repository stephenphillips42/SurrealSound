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

using namespace std;

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    cout << "Usage: " << argv[0] << " host voterid..." << endl;
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
  if (!isInteger(argv[2])) {
    cout << "Voter ID must be an integer" << endl;
    exit(EXIT_FAILURE);
  }
  // RPC Call
  int voterid = atoi(argv[2]);
  RetVal *retval = rpc_addvoter_1(&voterid,cl);
  // RPC error checking
  if (retval == NULL) {
    cout << "Error: RPC call failed" << endl;
    exit(EXIT_FAILURE);
  }
  if (isError(retval->errcode)) {
    cout << "ADDVOTER: Error of type "
         << RPCErrCodeToString(retval->errcode) << endl;
  }
  else {
    cout << "ADDVOTER: Success of type: " 
         << RPCErrCodeToString(retval->errcode) << endl
         << "Return Value: " << retval->data << endl;
  }

  exit(EXIT_SUCCESS);
}



