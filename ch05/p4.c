#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
	} 
	else if (rc == 0) {
		// child: redirect standard output to a file
		close(STDOUT_FILENO);
		open("./output_p4", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		
		// now exec "wc"...
		char *myargs[3];
		myargs[0] = strdup("wc");				// program: "wc" word count
		myargs[1] = strdup("p3.c");			// arguement: file to count
		myargs[2] = NULL;								// marks end of array
		execvp(myargs[0], myargs);			// runs word count
		printf("this shouldn't print out");
	}
	else {
		// parent goes down this path
		int rc_wait = wait(NULL);
	}
	return 0;
}
