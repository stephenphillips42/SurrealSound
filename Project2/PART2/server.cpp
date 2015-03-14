#include "server.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

// Server function implementations

ErrCode ServerWorker::zeroize() {
  voters.clear();
  votes.clear();
  return TRUEVALUE;
}

ErrCode ServerWorker::addvoter(int voterid) {
  if (voters.count(voterid) > 0) {
    return EXISTS;
  }
  voters[voterid] = false;
  return OK;
}

ErrCode ServerWorker::votefor(int voterid, string name) {
  // Handle failure cases
  if (voters.count(voterid) == 0) {
    return NOTAVOTER;
  }
  if (voters[voterid]) {
    return ALREADYVOTED;
  }
  // Success! Now insert it and see if it is a new candidate
  voters[voterid] = true;
  votes[name]++;
  if (votes[name] == 1)
    return NEW;
  else
    return EXISTS;
}

vector<string> ServerWorker::listcandidates() {
  vector<string> candidatelist(votes.size()); // Number of votes
  int i = 0;
  for(map< string, int >::iterator it = votes.begin();
        it != votes.end(); ++it) {
    candidatelist[i] = it->first;
    ++i;
  }
  return candidatelist;
}

int ServerWorker::votecount(string name) {
  if (votes.count(name) == 0) // make sure we don't insert needlessly
    return -1;
  return votes[name];
}
