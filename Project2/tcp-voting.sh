#!/bin/bash
touch testudp.test
./add-voter-tcp 127.0.0.1 8269 1 >> testtcp.test
./add-voter-tcp 127.0.0.1 8269 2 >> testtcp.test
./vote-tcp 127.0.0.1 8269 bill 1 >> testtcp.test
./vote-tcp 127.0.0.1 8269 bob 2 >> testtcp.test

./list-candidates-tcp 127.0.0.1 8269
./vote-count-tcp 127.0.0.1 8269 bill >> testtcp.test
./vote-count-tcp 127.0.0.1 8269 bob >> testtcp.test
./vote-count-tcp 127.0.0.1 8269 joe >> testtcp.test




