#!/bin/bash
# Start server
./server-udp &
SERVERPID=$!
#HOSTADDR=spec07.seas.upenn.edu
HOSTADDR=localhost
PORT=8269


sleep 0.1

# Add voter tests
./add-voter-udp $HOSTADDR $PORT 1 
./add-voter-udp $HOSTADDR $PORT 2 
./add-voter-udp $HOSTADDR $PORT 1 

# Voting tests
./vote-udp $HOSTADDR $PORT bill 1 
./vote-udp $HOSTADDR $PORT bob 2 
./vote-udp $HOSTADDR $PORT bill 2 
./vote-udp $HOSTADDR $PORT bill 3 

# Candidate tests
./list-candidates-udp $HOSTADDR $PORT
./vote-count-udp $HOSTADDR $PORT bill 
./vote-count-udp $HOSTADDR $PORT bob 
./vote-count-udp $HOSTADDR $PORT joe 

# Zeroize tests
./vote-zero-udp $HOSTADDR $PORT 

echo
echo Zeroize
echo

# Add voter tests
./add-voter-udp $HOSTADDR $PORT 1 
./add-voter-udp $HOSTADDR $PORT 2 
./add-voter-udp $HOSTADDR $PORT 1 

# Voting tests
./vote-udp $HOSTADDR $PORT bill 1 
./vote-udp $HOSTADDR $PORT bob 2 

# Candidate tests
./list-candidates-udp $HOSTADDR $PORT
./vote-count-udp $HOSTADDR $PORT bill 
./vote-count-udp $HOSTADDR $PORT bob 
./vote-count-udp $HOSTADDR $PORT joe 


if kill $SERVERPID; then { echo; echo Server finished; } fi

