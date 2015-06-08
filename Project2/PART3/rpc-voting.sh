#!/bin/bash
# Start server
./server-rpc &
SERVERPID=$!
#HOSTADDR=spec07.seas.upenn.edu
HOSTADDR=localhost

sleep 0.1

# Add voter tests
./add-voter-rpc $HOSTADDR 1 
./add-voter-rpc $HOSTADDR 2 
./add-voter-rpc $HOSTADDR 1 

# Voting tests
./vote-rpc $HOSTADDR bill 1 
./vote-rpc $HOSTADDR bob 2 
./vote-rpc $HOSTADDR bill 2 
./vote-rpc $HOSTADDR bill 3 
./add-voter-rpc $HOSTADDR 3 
./vote-rpc $HOSTADDR bill 3 

# Candidate tests
./list-candidates-rpc $HOSTADDR
./vote-count-rpc $HOSTADDR bill 
./vote-count-rpc $HOSTADDR bob 
./vote-count-rpc $HOSTADDR joe 

# Zeroize tests
./vote-zero-rpc $HOSTADDR 

echo
echo Zeroize
echo

# Add voter tests
./add-voter-rpc $HOSTADDR 1 
./add-voter-rpc $HOSTADDR 2 
./add-voter-rpc $HOSTADDR 1 

# Voting tests
./vote-rpc $HOSTADDR bill 1 
./vote-rpc $HOSTADDR bob 2 

# Candidate tests
./list-candidates-rpc $HOSTADDR
./vote-count-rpc $HOSTADDR bill 
./vote-count-rpc $HOSTADDR bob 
./vote-count-rpc $HOSTADDR joe 


if kill $SERVERPID; then { echo; echo Server finished; } fi

