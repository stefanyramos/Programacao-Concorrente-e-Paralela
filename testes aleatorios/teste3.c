#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine(void* arg) {
    int index = *(int*)arg;
    int i;

    printf("%d\n", index);

    printf ("Thread %d...\n", index);

    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    int* a = malloc(sizeof(int));
    *a = 0;

    pthread_mutex_init(&mutex, NULL);
    
    pthread_t th[4];
    int i;

    for (i=0; i<4; i++){
        int* a = malloc(sizeof(int));
        *a = i +1;

        pthread_create(&th[i], NULL, &routine, a);
    }

    for (i=0; i<4; i++){
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Number of mails: %d\n", mails);
    return 0;
}