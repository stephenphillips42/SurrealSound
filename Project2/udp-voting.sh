#!/bin/bash
touch testudp.test
./add-voter-udp 127.0.0.1 8269 1 >> testudp.test
./add-voter-udp 127.0.0.1 8269 2 >> testudp.test
./vote-udp 127.0.0.1 8269 bill 1 >> testudp.test
./vote-udp 127.0.0.1 8269 bob 2 >> testudp.test

./list-candidates-udp 127.0.0.1 8269
./vote-count-udp 127.0.0.1 8269 bill >> testudp.test
./vote-count-udp 127.0.0.1 8269 bob >> testudp.test
./vote-count-udp 127.0.0.1 8269 joe >> testudp.test




