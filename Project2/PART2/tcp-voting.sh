#!/bin/bash
# Start server
./server-tcp &
SERVERPID=$!

sleep 0.1

# Add voter tests
./add-voter-tcp 127.0.0.1 8269 1 
./add-voter-tcp 127.0.0.1 8269 2 
./add-voter-tcp 127.0.0.1 8269 1 

# Voting tests
./vote-tcp 127.0.0.1 8269 bill 1 
./vote-tcp 127.0.0.1 8269 bob 2 
./vote-tcp 127.0.0.1 8269 bill 2 
./vote-tcp 127.0.0.1 8269 bill 3 

# Candidate tests
./list-candidates-tcp 127.0.0.1 8269
./vote-count-tcp 127.0.0.1 8269 bill 
./vote-count-tcp 127.0.0.1 8269 bob 
./vote-count-tcp 127.0.0.1 8269 joe 

# Zeroize tests
./vote-zero-tcp 127.0.0.1 8269

echo
echo Zeroize
echo

# Add voter tests
./add-voter-tcp 127.0.0.1 8269 1 
./add-voter-tcp 127.0.0.1 8269 2 
./add-voter-tcp 127.0.0.1 8269 1 

# Voting tests
./vote-tcp 127.0.0.1 8269 bill 1 
./vote-tcp 127.0.0.1 8269 bob 2 

# Candidate tests
./list-candidates-tcp 127.0.0.1 8269
./vote-count-tcp 127.0.0.1 8269 bill 
./vote-count-tcp 127.0.0.1 8269 bob 
./vote-count-tcp 127.0.0.1 8269 joe 


if kill $SERVERPID; then { echo; echo Server finished; } fi

