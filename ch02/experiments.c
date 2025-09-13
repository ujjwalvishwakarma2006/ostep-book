#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/wait.h>  // for wait()

int main() {
  // Experiment-1:
  for (int i = 0; i < 10; ++i) {
    int x = 10;
    printf("Address of x = %p\n", (void*)&x);
  }

  // Experiment-2:
  int a = 0;
  int *p1 = &a;
  *p1 = 10;
  printf("From parent, p1 = %d\n", *p1);
  printf("From parent, Add(p1) = %p\n", (void*)&p1);

  int *p2 = NULL;
  printf("From parent, Add(p2) = %p\n", (void*)&p2);

  pid_t pid = fork();
  assert(pid >= 0);

  int x = 69; // variable local to main()

  if (pid == 0) {  // Child process
    *p1 = 100;  // modifies child's copy of 'a'
    printf("From Child, p1 = %d\n", *p1);
    printf("From Child, Add(p1) = %p\n", (void*)&p1);

    p2 = &x;  // p2 points to local variable x in child
    printf("From Child, p2 = %d\n", *p2);
    printf("From Child, Add(p2) = %p\n", (void*)&p2);

    exit(0);
  } else {  // Parent process
    wait(NULL);  // wait for child to finish
    printf("From parent, p1 = %d\n", *p1);
    if (p2 == NULL) {
      printf("From Parent, p2 is NULL (uninitialized)\n");
    } else {
      printf("From Parent, p2 = %d\n", *p2);
    }
  }

  return 0;
}

