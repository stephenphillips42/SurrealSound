#include <vector>
#include <map>
#include <set>
#include <vector>
#include <string>

// Error code of function
typedef enum {
  OK           =  0,
  NEW          =  1,
  EXISTS       =  2,
  ERROR        = -1,
  NOTAVOTER    = -2,
  ALREADYVOTED = -3
} ErrCode;


class ServerWorker {
public:
  // zeroize
  // Input: None
  // Description: Sets this to inital state, with zero candidates, voters,
  //              and votes
  // Output: TRUE  - if successful
  //         FALSE - otherwise
  bool zeroize();

  // addvoter
  // Input: voterid - integer ID
  // Description: Adds voter voterid to the list of registered voters
  // Output: OK     - if successful
  //         EXISTS - if voterid already exists
  //         ERROR  - if the operation failed
  ErrCode addvoter(int voterid);

  // votefor
  // Input: name    - non-empty string of the name of the candidate
  //        voterid - integer ID of voter
  // Description: Makes voterid vote for person specified by name. If that
  //              voterid has already voted or has not registered, then it
  //              will not change the list of voters for that candidate
  // Output: NEW          - if name is a new candidate
  //         EXISTS       - if name already in database
  //         NOTAVOTER    - if voterid not in list of registered voters
  //         ALREADYVOTED - if voterid has already voted
  //         ERROR        - if the operation failed
  ErrCode votefor(std::string name, int voterid);

  // listcandidates
  // Input: None
  // Description: Lists the candidates that have votes (order arbitrary)
  // Output: An array of null-terminated strings of the names of the voters
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

  // Helper functions
  bool isInteger(std::string s);
};
