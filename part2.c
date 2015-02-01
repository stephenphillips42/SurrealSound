/* stdlibrary_writer.c ‐ write 400,000 characters with fprintf */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// #define STDLIB_OUTPUT_NAME "fprint.out"
// #define SYSCALL_OUTPUT_NAME "write.out"

main()
{
  long i;
  FILE *fp;
  if ((fp=fopen(OUTPUTNAME,"w")) == NULL) {
    fprintf(stderr,"Can't open %s. Bye.\n",OUTPUTNAME);
    exit(1);
  }
  for (i=0; i<400000; i++) { /* write 400,000 Xs with fprintf */
    if (fprintf(fp,"X") < 1) {
      fprintf(stderr,"Can't write. Bye\n");
      exit(1);
    }
  }
  fclose(fp);
  exit(0);
}

/* syscall_writer.c ‐ write 50,000 characters with write*/

main()
{
	long i;
	int fd;
	if ((fd=open(OUTPUTNAME,O_WRONLY|O_CREAT,0644)) < 0) {
		fprintf(stderr,"Can't open %s. Bye.\n",OUTPUTNAME);
		exit(1);
	}
	for (i=0; i<50000; i++) { /* write 50,000 Ys with write */
		if (write(fd,"Y",1) < 1) {
			fprintf(stderr,"Can't write. Bye\n");
			exit(1);
		}
	}
	close(fd);
	exit(0);
}

