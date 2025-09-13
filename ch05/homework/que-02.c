// Behaviour of the program is non-deterministic.
// But you have to try many many time to see that.
// You can use the following command after compiling the code:
// ./que-02.o && cat somefile.txt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	
	// not truncating the length of the opened file to zero
	close(STDOUT_FILENO);
	int fd = open("./somefile.txt", O_WRONLY | O_CREAT, S_IRWXU);
	printf("%d\n", fd);
	
	int rc = fork();
	
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	}
	else if (rc == 0) {
		// child is able to access the file descriptor
		printf("I am child, fd = %d\n", fd);
		// since printf uses buffer and prints in chunks, it will be,
		// almost all the time, printed after write calls
		
		write(fd, "Written by child\n", 17);
		write(fd, "Written by child\n", 17);
		write(fd, "Written by child\n", 17);
		write(fd, "Written by child\n", 17);
	}
	else {
		// parent is also able to access the file descriptor
		printf("I am parent, fd = %d\n", fd);
		// since printf uses buffer and prints in chunks, it will be,
		// almost all the time, printed after write calls
		
		write(fd, "Written by parent\n", 18);
		write(fd, "Written by parent\n", 18);
		write(fd, "Written by parent\n", 18);
		write(fd, "Written by parent\n", 18);
	}
	
	return 0;
}
