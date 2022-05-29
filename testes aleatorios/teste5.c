#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* routine(void* arg) {
    int id = *(int*)arg;
    printf ("Thread %d...\n", id);
  
    if (pthread_mutex_trylock(&mutex) == 0){
        printf("Got lock\n");
        sleep(3);
        pthread_mutex_unlock(&mutex);
    } else {
        printf("Didn't lock\n");
    }
    

    //*(int*)arg = index;
    //return arg;
    } 

    int main() {
    pthread_mutex_init(&mutex, NULL);
    
    pthread_t th[4];
    int i;

    for (i=0; i<4; i++){
        int* a = malloc(sizeof(int));
        *a =i;
        pthread_create(&th[i], NULL, &routine, a);
    }

    for (i=0; i<4; i++){
        int* r;
        pthread_join(th[i], (void**)&r);
        
    }

    pthread_mutex_destroy(&mutex);

    return 0;

}