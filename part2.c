#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// pthreads library
#include <pthread.h>
// Timing library (thanks piazza)
#include <time.h>

// Output files
#define STDLIB_OUTPUT_NAME "fprint.out"
#define SYSCALL_OUTPUT_NAME "write.out"

// Output times
struct timespec g_timestart;
struct timespec g_syscall_time;
struct timespec g_stdlib_time;

/* syscall_writer.c ‐ write 50,000 characters with write*/
void * syscall_writer(void * arg)
{
  (void)(arg);
  long i;
  int fd;
  if ((fd=open(SYSCALL_OUTPUT_NAME,O_WRONLY|O_CREAT,0644)) < 0) {
    fprintf(stderr,"Can't open %s. Bye.\n",SYSCALL_OUTPUT_NAME);
    exit(1);
  }
  for (i=0; i<50000; i++) { /* write 50,000 Ys with write */
    if (write(fd,"Y",1) < 1) {
      fprintf(stderr,"Can't write. Bye\n");
      exit(1);
    }
  }
  close(fd);
  // Getting finish time for later output
  clock_gettime(CLOCK_MONOTONIC, &g_syscall_time);
  // Report completion the old fashioned way
  printf("Finished syscall_writer\n");
  return 0;
}

/* stdlibrary_writer.c ‐ write 400,000 characters with fprintf */
void * stdlib_writer(void * arg)
{
  (void)(arg);
  long i;
  FILE *fp;
  if ((fp=fopen(STDLIB_OUTPUT_NAME,"w")) == NULL) {
    fprintf(stderr,"Can't open %s. Bye.\n",STDLIB_OUTPUT_NAME);
    exit(1);
  }
  for (i=0; i<400000; i++) { /* write 400,000 Xs with fprintf */
    if (fprintf(fp,"X") < 1) {
      fprintf(stderr,"Can't write. Bye\n");
      exit(1);
    }
  }
  fclose(fp);
  // Getting finish time for later output
  clock_gettime(CLOCK_MONOTONIC, &g_stdlib_time);
  // Report completion the old fashioned way
  printf("Finished stdlib_writer\n");


  return 0;
}

// Main function to run the threads
int main()
{
  pthread_t thread_id1;
  pthread_t thread_id2;

  // Setup start time                                                                                                                                                                                                                       
  clock_gettime(CLOCK_MONOTONIC, &g_timestart);

  // Create the threads
  pthread_create(&thread_id1,NULL,syscall_writer,NULL);
  pthread_create(&thread_id2,NULL,stdlib_writer,NULL);

  // Join the threads  
  pthread_join(thread_id1,NULL);
  pthread_join(thread_id2,NULL);

  return 0;
}




