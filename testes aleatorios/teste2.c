#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int v[SIZE];
int g = 0;

void * function (void *arg) {
  printf("test\n");
  sleep(3);
  printf("ending\n");
}

int main(){
  pthread_t t1, t2;
  int a1 = 1;
  int a2 = 2;
  int i;

  pthread_create(&t1, NULL, *function, (void *)(&a1));
  pthread_create(&t2, NULL, *function, (void *)(&a2));

  pthread_join(t1, NULL);
  // pthread_join(t2, NULL);

  
  exit(0);

  return 0;
}