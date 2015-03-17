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

// Good old 'to string' implementation
#include <sstream>
#define SSTR( x ) ((dynamic_cast< std::ostringstream & > \
         ( std::ostringstream() << std::dec << x )).str()) 

using namespace std;

int
main(int argc, char *argv[])
{
  if (argc < 3) {
    cout << "Usage: " << argv[0] << " host port..." << endl;
    exit(EXIT_FAILURE);
  }
  RetVal *retval = rpc_zeroize_1();

  if (retval->errcode < 0) {
    cout << "ZEROIZE: Success of type: " 
         << RPCErrCodeToString(retval->errcode) << endl
         << "Return Value: " << retval->data << endl;
  else {
    cout << "ZEROIZE: Error of type "
         << RPCErrCodeToString(retval->errcode) << endl;
  }


  exit(EXIT_SUCCESS);
}
