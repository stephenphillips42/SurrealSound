#!/bin/bash
# Start server
./server-udp &
SERVERPID=$!

# Add voter tests
./add-voter-udp 127.0.0.1 8269 1 
./add-voter-udp 127.0.0.1 8269 2 
./add-voter-udp 127.0.0.1 8269 1 

# Voting tests
./vote-udp 127.0.0.1 8269 bill 1 
./vote-udp 127.0.0.1 8269 bob 2 
./vote-udp 127.0.0.1 8269 bill 2 

# Candidate tests
./list-candidates-udp 127.0.0.1 8269
./vote-count-udp 127.0.0.1 8269 bill 
./vote-count-udp 127.0.0.1 8269 bob 
./vote-count-udp 127.0.0.1 8269 joe 

# Zeroize tests
./zeroize-udp 127.0.0.1 8269 

echo
echo Zeroize
echo

# Add voter tests
./add-voter-udp 127.0.0.1 8269 1 
./add-voter-udp 127.0.0.1 8269 2 
./add-voter-udp 127.0.0.1 8269 1 

# Voting tests
./vote-udp 127.0.0.1 8269 bill 1 
./vote-udp 127.0.0.1 8269 bob 2 

# Candidate tests
./list-candidates-udp 127.0.0.1 8269
./vote-count-udp 127.0.0.1 8269 bill 
./vote-count-udp 127.0.0.1 8269 bob 
./vote-count-udp 127.0.0.1 8269 joe 


if kill $SERVERPID; then { echo; echo Server finished; } fi

