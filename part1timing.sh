#!/bin/bash

# stdlibrary_writer  syscall_writer
echo Timing the system call writer ...

for i in `seq 1 10`
do
    /usr/bin/time -f "%e time elapsed, with %P CPU. %c involuntary context-switches, %w voluntary context switches (I/O)" ./bin/syscall_writer
done


echo Timing the standard library writer ...
for i in `seq 1 10`
do
    /usr/bin/time -f "%e time elapsed, with %P CPU. %c involuntary context-switches, %w voluntary context switches (I/O)" ./bin/stdlibrary_writer
done

echo Finished
