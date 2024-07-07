#include <stdio.h>
#include <stdlib.h>
#include "sys/syssgi.h"
#include "sys/types.h"

char empty[] = {0};

extern int errno;
	
main(int argc, char *argv[])
{	
	__uint64_t pp[5];
	int i;
	volatile caddr_t addr;
	volatile long long x;
	pid_t pid = getpid();

	printf("pid is %d\n", pid);

	for (i = 1; i < argc; i++) {	
	  pp[i-1] = strtoull(argv[i], NULL, 0);
	  printf("Arg %d is 0x%llx\n", i, pp[i-1]);
	}

	fflush(stdout);
	addr = malloc(65536);
	if (addr == NULL) {
	  printf("unable to alloc mem\n");
	  exit(-1);
	}
	
	/* WHat the hell is this? */
	addr = (caddr_t)((__uint64_t)(addr + 0x3fff) & ~0x3fff);

	/* read */
	if (pp[2] & 0x80) 
	  x = *addr;
	
	/* write */
	if (pp[2] & 0x100)
	  *addr = 5;

	pp[1] = (__uint64_t)addr;
	pp[2] |= 0x40;
	if (syssgi(SGI_ERROR_FORCE, pp[0], pp[1], pp[2], pp[3], pp[4]) == -1) {
		printf("error num %d\n", errno);
		exit(-1);
	}
	if (pp[2] & 0x80) 
	    x = *addr;
	
	if (pp[2] & 0x100)
	    *addr = 5;

	if (syssgi(SGI_ERROR_FORCE, 16, pp[1], 64|0x0f20000, pp[3], pp[4]) == -1) {
		printf("flush error num %d\n", errno);
		exit(-1);
	}

	if (syssgi(SGI_ERROR_FORCE, 18, pp[1], 64, pp[3], pp[4]) == -1) {
		printf("flush error num %d\n", errno);
		exit(-1);
	}

	if (pp[2] & 0x80) 
	    x = *addr;
	
	if (pp[2] & 0x100)
	    *addr = 5;


}










