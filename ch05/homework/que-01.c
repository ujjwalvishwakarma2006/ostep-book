#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	
	int x = 100;
	int rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (rc == 0) {
		// value of x will only be changed in the child process,
		// and will not reflect in the parent process's memory.
		printf("value of x in child before updating = %d\n", x);
		x = 101;
		printf("value of x in child after updating = %d\n", x);
	}
	else {
		// x is still 100, not 101.
		printf("value of x in parent before updating = %d\n", x);
		x = 99;
		printf("value of x in parent after updating = %d\n", x);
	}
	
	return 0;
}
