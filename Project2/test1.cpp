// Testing code for the server
// Author: Stephen Phillips
// PennKey: stephi
// PennID: 14378269
#include "server.h"
#include <stdlib.h>
#include <iostream>
#include <set>
#include <assert.h>

using namespace std;

// Run the server
int main(int argc, char *argv[]) {
	cout << "Testing...\n";
	// General idea:
	// Create socket with port 8269 (datagram, INET?)
	// Use select to wait for something to come
	// When something does come, check the packet and process it accordingly
	ServerWorker server;
	// Voters' tests
	assert(server.addvoter(1) == OK);
  assert(server.addvoter(1) == EXISTS);
  assert(server.addvoter(12) == OK);
	assert(server.addvoter(15) == OK);
	assert(server.addvoter(-25) == OK);

	// Voting tests
	assert(server.votefor("Bobby",1) == NEW);
	assert(server.votefor("Bobby",1) == ALREADYVOTED);
	assert(server.votefor("Bobby",12) == EXISTS);
	assert(server.votefor("Billy",15) == NEW);
	assert(server.votefor("Billy",127) == NOTAVOTER);
	assert(server.votefor("Joey",-25) == NEW);

	// Zeroize test
	assert(server.zeroize());
	assert(server.addvoter(1) == OK);
	assert(server.addvoter(15) == OK);
  assert(server.addvoter(12) == OK);
  assert(server.addvoter(1) == EXISTS);
	assert(server.addvoter(-25) == OK);
	assert(server.votefor("Bobby",1) == NEW);
	assert(server.votefor("Bobby",-25) == EXISTS);
	assert(server.votefor("Billy",21) == NOTAVOTER);
	assert(server.votefor("Billy",15) == NEW);
	assert(server.votefor("Joey",-25) == ALREADYVOTED);
	assert(server.votefor("Joey",12) == NEW);

	// List candidates test
	set<string> candidates;
	candidates.insert("Bobby");
	candidates.insert("Billy");
	candidates.insert("Joey");
	// vector<string> mycandidates = server.listcandidates();

}
