#!/bin/bash

./add-voter-udp localhost 8269 1
./add-voter-udp localhost 8269 2
./vote-udp localhost 8269 bill 1
./vote-udp localhost 8269 bob 2

./list-candidates-udp localhost 8269
./vote-count-udp localhost 8269 bill
./vote-count-udp localhost 8269 bob
./vote-count-udp localhost 8269 joe



