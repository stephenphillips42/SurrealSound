CC=gcc
CFLAGS=-pthread -Wall

all: part1 part2 part3

part1: 
	$(CC) syscall_writer.c -o bin/syscall_writer
	$(CC) stdlibrary_writer.c -o bin/stdlibrary_writer

part2:
	$(CC) $(CFLAGS) part2.c -o bin/part2

part3:
	$(CC) $(CFLAGS) part3.c -o bin/part3

clean:
	rm -rf bin/* *out
