#!/bin/bash
# Start server
./server-tcp &
SERVERPID=$!
#HOSTADDR=spec01.seas.upenn.edu
HOSTADDR=localhost
PORT=8269

sleep 0.1

# Add voter tests
./add-voter-tcp $HOSTADDR $PORT 1 
./add-voter-tcp $HOSTADDR $PORT 2 
./add-voter-tcp $HOSTADDR $PORT 1 

# Voting tests
./vote-tcp $HOSTADDR $PORT bill 1 
./vote-tcp $HOSTADDR $PORT bob 2 
./vote-tcp $HOSTADDR $PORT bill 2 
./vote-tcp $HOSTADDR $PORT bill 3 
./add-voter-tcp $HOSTADDR $PORT 3 
./vote-tcp $HOSTADDR $PORT bill 3 

# Candidate tests
./list-candidates-tcp $HOSTADDR $PORT
./vote-count-tcp $HOSTADDR $PORT bill 
./vote-count-tcp $HOSTADDR $PORT bob 
./vote-count-tcp $HOSTADDR $PORT joe 

# Zeroize tests
./vote-zero-tcp $HOSTADDR $PORT

echo
echo Zeroize
echo

# Add voter tests
./add-voter-tcp $HOSTADDR $PORT 1 
./add-voter-tcp $HOSTADDR $PORT 2 
./add-voter-tcp $HOSTADDR $PORT 1 

# Voting tests
./vote-tcp $HOSTADDR $PORT bill 1 
./vote-tcp $HOSTADDR $PORT bob 2 

# Candidate tests
./list-candidates-tcp $HOSTADDR $PORT
./vote-count-tcp $HOSTADDR $PORT bill 
./vote-count-tcp $HOSTADDR $PORT bob 
./vote-count-tcp $HOSTADDR $PORT joe 


if kill $SERVERPID; then { echo; echo Server finished; } fi

