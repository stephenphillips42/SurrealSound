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
	assert(server.votefor(1,"Bobby") == NEW);
	assert(server.votefor(1,"Bobby") == ALREADYVOTED);
	assert(server.votefor(12,"Bobby") == EXISTS);
	assert(server.votefor(15,"Billy") == NEW);
	assert(server.votefor(127,"Billy") == NOTAVOTER);
	assert(server.votefor(-25,"Joey") == NEW);

	// Zeroize test
	assert(server.zeroize() == TRUEVALUE);
	assert(server.addvoter(1) == OK);
	assert(server.addvoter(15) == OK);
	assert(server.addvoter(12) == OK);
	assert(server.addvoter(1) == EXISTS);
	assert(server.addvoter(-25) == OK);
	assert(server.votefor(1,"Bobby") == NEW);
	assert(server.votefor(-25,"Bobby") == EXISTS);
	assert(server.votefor(21,"Billy") == NOTAVOTER);
	assert(server.votefor(15,"Billy") == NEW);
	assert(server.votefor(-25,"Joey") == ALREADYVOTED);
	assert(server.votefor(12,"Joey") == NEW);

	// List candidates test
	set<string> candidates;
	candidates.insert("Bobby");
	candidates.insert("Billy");
	candidates.insert("Joey");
	vector<string> mycandidates = server.listcandidates();
	for(unsigned int i = 0; i < mycandidates.size(); ++i) {
		assert(candidates.count(mycandidates[i]) > 0);
	}
	// Vote count test
	assert(server.votecount("Bobby") == 2);
	assert(server.votecount("Billy") == 1);
	assert(server.votecount("Joey") == 1);
	assert(server.votecount("Tammy") == -1);

}
