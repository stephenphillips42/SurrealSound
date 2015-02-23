// Server code for electronic voting system
// Author: Stephen Phillips
// PennKey: stephi
// PennID: 14378269

#include <stdlib.h>
#include <stdio.h>

// Custom return value declarations
// Success value of call
typedef enum {
	TRUE = 1,
	FALSE = 0
} success_val;

// Error code of function
typedef enum {
	OK           =  0,
	NEW          =  1,
	EXISTS       =  2,
	ERROR        = -1,
	NOTAVOTER    = -2,
	ALREADYVOTED = -3
} err_code;

// Function headers
success_val zeroize();
err_code addvoter(int);
err_code votefor(char*,int);
char **listcandidates();
int votecount(char*);

// Run the server
int main(int argc, char *argv[]) {
	printf("Just beginning\n");
	// General idea:
	// Create socket with port 8269 (datagram, INET?)
	// Use select to wait for something to come
	// When something does come, check the packet and process it accordingly

}

// Support functions

// zeroize
// Input: None
// Description: Sets initial to inital state, with zero candidates, voters,
//              and votes
// Output: TRUE  - if successful
//         FALSE - otherwise
success_val zeroize() {
	return TRUE;
}

// addvoter
// Input: voterid - integer ID 
// Description: Adds voter voterid to the list of registered voters
// Output: OK     - if successfull
//         EXISTS - if voterid already exists
//         ERROR  - if the operation failed
err_code addvoter(int voterid) {
	(void)(voterid);
	return OK;
}

// votefor
// Input: name    - string of the name of the candidate
//        voterid - integer ID of voter
// Description: Makes voterid vote for person specified by name
// Output: NEW          - if name is a new candidate
//         EXISTS       - if name already in database
//         NOTAVOTER    - if voterid not in list of registered voters
//         ALREADYVOTED - if voterid has already voted
//         ERROR        - if the operation failed
err_code votefor(char *name, int voterid) {
	(void)(name);
	(void)(voterid);
	return OK;
}

// listcandidates
// Input: None
// Description: Lists the candidates that have votes (order arbitrary)
// Output: An array of null-terminated strings of the names of the voters
char **listcandidates() {
	return 0;
}

// votecount
// Input: name - string of name of candidate
// Description: Returns how many votes for the candidate 'name'
// Output: -1 if candidate does not exist, otherwise the number of votes 
//         the candidate has
int votecount(char *name) {
	return OK;
}






