#include "server.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

// Server function implementations

bool ServerWorker::zeroize() {
  voters.clear();
  votes.clear();
  return true;
}

ErrCode ServerWorker::addvoter(int voterid) {
  if (voters.count(voterid) > 0) {
    return EXISTS;
  }
  voters[voterid] = false;
  return OK;
}

ErrCode ServerWorker::votefor(string name, int voterid) {
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
  for(map< string, int >::iterator it = votes.end();
        it != votes.end(); ++it) {
    candidatelist[i] = it->first;
    ++i;
  }
  return candidatelist;
}

int ServerWorker::votecount(string name) {
  return 0;
}

// The C++ API uses exceptions to check for failure, which is just overkill, so
// this function just checks that it is an integer
bool isInteger(string s) {
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    return false;
  char * p;
  strtol(s.c_str(), &p, 10);
  return (*p == 0);
}
