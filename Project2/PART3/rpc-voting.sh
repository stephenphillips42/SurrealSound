#!/bin/bash
# Start server
./server-rpc &
SERVERPID=$!

# Add voter tests
./add-voter-rpc 127.0.0.1 1 
./add-voter-rpc 127.0.0.1 2 
./add-voter-rpc 127.0.0.1 1 

# Voting tests
./vote-rpc 127.0.0.1 bill 1 
./vote-rpc 127.0.0.1 bob 2 
./vote-rpc 127.0.0.1 bill 2 

# Candidate tests
./list-candidates-rpc 127.0.0.1
./vote-count-rpc 127.0.0.1 bill 
./vote-count-rpc 127.0.0.1 bob 
./vote-count-rpc 127.0.0.1 joe 

# Zeroize tests
./zeroize-rpc 127.0.0.1 

echo
echo Zeroize
echo

# Add voter tests
./add-voter-rpc 127.0.0.1 1 
./add-voter-rpc 127.0.0.1 2 
./add-voter-rpc 127.0.0.1 1 

# Voting tests
./vote-rpc 127.0.0.1 bill 1 
./vote-rpc 127.0.0.1 bob 2 

# Candidate tests
./list-candidates-rpc 127.0.0.1
./vote-count-rpc 127.0.0.1 bill 
./vote-count-rpc 127.0.0.1 bob 
./vote-count-rpc 127.0.0.1 joe 


if kill $SERVERPID; then { echo; echo Server finished; } fi

