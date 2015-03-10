// Server code for electronic voting system
// Author: Stephen Phillips
// PennKey: stephi
// PennID: 14378269
#include "server.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

// Run the server
int main(int argc, char *argv[]) {
	// General idea:
	// Create socket with port 8269 (datagram, INET?)
	// Use select to wait for something to come
	// When something does come, check the packet and process it accordingly
	cout << "Hello world" << endl;
}
