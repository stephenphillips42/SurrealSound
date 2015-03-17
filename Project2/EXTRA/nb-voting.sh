#!/bin/bash
# Start server
./server-nb &
SERVERPID=$!

sleep 0.1

# Add voter tests
./add-voter-nb 127.0.0.1 8269 1 
./add-voter-nb 127.0.0.1 8269 2 
./add-voter-nb 127.0.0.1 8269 1 

# Voting tests
./vote-nb 127.0.0.1 8269 bill 1 
./vote-nb 127.0.0.1 8269 bob 2 
./vote-nb 127.0.0.1 8269 bill 2 
./vote-nb 127.0.0.1 8269 bill 3 

# Candidate tests
./list-candidates-nb 127.0.0.1 8269
./vote-count-nb 127.0.0.1 8269 bill 
./vote-count-nb 127.0.0.1 8269 bob 
./vote-count-nb 127.0.0.1 8269 joe 

# Zeroize tests
./vote-zero-nb 127.0.0.1 8269

echo
echo Zeroize
echo

# Add voter tests
./add-voter-nb 127.0.0.1 8269 1 
./add-voter-nb 127.0.0.1 8269 2 
./add-voter-nb 127.0.0.1 8269 1 

# Voting tests
./vote-nb 127.0.0.1 8269 bill 1 
./vote-nb 127.0.0.1 8269 bob 2 

# Candidate tests
./list-candidates-nb 127.0.0.1 8269
./vote-count-nb 127.0.0.1 8269 bill 
./vote-count-nb 127.0.0.1 8269 bob 
./vote-count-nb 127.0.0.1 8269 joe 


if kill $SERVERPID; then { echo; echo Server finished; } fi

