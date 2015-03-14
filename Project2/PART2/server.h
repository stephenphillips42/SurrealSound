#ifndef SERVERH
#define SERVERH value

#include <vector>
#include <map>
#include <set>
#include <vector>
#include <string>

#include "errorcode.h"

class ServerWorker {
public:
  // zeroize
  // Input: None
  // Description: Sets this to inital state, with zero candidates, voters,
  //              and votes
  // Output: TRUEVALUE  - if successful
  //         FALSEVALUE - otherwise
  ErrCode zeroize();

  // addvoter
  // Input: voterid - integer ID
  // Description: Adds voter voterid to the list of registered voters
  // Output: OK     - if successful
  //         EXISTS - if voterid already exists
  //         ERROR  - if the operation failed
  ErrCode addvoter(int voterid);

  // votefor
  // Input: voterid - integer ID of voter
  //        name    - non-empty string of the name of the candidate
  // Description: Makes voterid vote for person specified by name. If that
  //              voterid has already voted or has not registered, then it
  //              will not change the list of voters for that candidate
  // Output: NEW          - if name is a new candidate
  //         EXISTS       - if name already in database
  //         NOTAVOTER    - if voterid not in list of registered voters
  //         ALREADYVOTED - if voterid has already voted
  //         ERROR        - if the operation failed
  ErrCode votefor(int voterid, std::string name);

  // listcandidates
  // Input: None
  // Description: Lists the candidates that have votes (order arbitrary)
  // Output: An array of strings of the names of the voters
  std::vector<std::string> listcandidates();

  // votecount
  // Input: name - string of name of candidate
  // Description: Returns how many votes for the candidate 'name'
  // Output: -1 if candidate does not exist, otherwise the number of votes
  //         the candidate has
  int votecount(std::string name);
private:
  // Maps voterids to if the voterid has voted or not
  std::map< int, bool > voters;
  // Candidates are the keys, the number of votes is the value
  std::map< std::string, int > votes;
};

#endif
