CC=gcc
CFLAGS=-c -Wall

all: part1
# part2 part3

part1: 
	$(CC) syscall_writer.c -o bin/syscall_writer
	$(CC) stdlibrary_writer.c -o bin/stdlibrary_writer

#main.o: main.cpp
#	$(CC) $(CFLAGS) main.cpp

#factorial.o: factorial.cpp
#	$(CC) $(CFLAGS) factorial.cpp

#hello.o: hello.cpp
#	$(CC) $(CFLAGS) hello.cpp

clean:
	rm -rf *o hello
