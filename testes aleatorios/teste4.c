#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 8

int primes[SIZE] = {2, 3, 5, 7, 11, 13, 17, 19};

void* routine(void* arg) {
  int index = *(int*)arg;
  int i;
  int sum = 0;

  
  printf ("Thread %d...\n", index);
  sleep(3);
  printf ("Thread %d ending...\n", index);

  for(i=0; i<SIZE/2; i++){
    sum += primes[index];
    index++;
  }

  printf("%d\n", sum);

  *(int*)arg = sum;
  return arg;
  
} 

int main() {
  int* res;
  srand(time(NULL));
  pthread_t th[2];
  int i;

  for (i=0; i<2; i++){
    int* a = malloc(sizeof(int));
    *a = i * (SIZE/2);

    pthread_create(&th[i], NULL, &routine, a);
  }

  int global_sum = 0;
  for (i=0; i<2; i++){
    int* r;
    pthread_join(th[i], (void**)&r);
    global_sum += *r;
    free(r);
  }

  printf("global sum: %d\n", global_sum);
  return 0;

}