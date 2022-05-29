#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

# define TH_NUM 6

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void* arg) {
    int id = *(int*)arg;
    // printf ("Thread fuel_filling %d...\n", id);

	for(int i=0; i<5; i++){
		pthread_mutex_lock(&mutexFuel);
		fuel += 30;
		printf ("gas bomb %d filled fuel %d\n", id, fuel);
		pthread_mutex_unlock(&mutexFuel);
		// pthread_cond_signal(&condFuel); // sinal pra uma thread de cada vez
		pthread_cond_broadcast(&condFuel); // sinal para todas as threads 'broadcast'
	}

    //*(int*)arg = index;
    //return arg;
} 

void* car(void* arg){
	int id = *(int*)arg;
    // printf ("Thread car %d...\n", id);
	
	while(fuel < 40){
		printf("No fuel for car %d. Waiting...\n", id);
		pthread_cond_wait(&condFuel, &mutexFuel);
		/*
		  * Equivalent to:
		  * pthread_mutex_unlock(&mutexFuel);
		  * WAIT for Signal on condFuel
		  * pthread_mutex_lock(&mutexFuel);
		*/

		sleep(1);
	}
	//pthread_mutex_lock(&mutexFuel);
	fuel -= 40;
	printf ("car %d got fuel now left:  %d\n", id, fuel);
	pthread_mutex_unlock(&mutexFuel);

}

int main() {
    pthread_mutex_init(&mutexFuel, NULL);
	pthread_cond_init(&condFuel, NULL);
    
    pthread_t th[TH_NUM];
    int i;

    for (i=0; i<TH_NUM; i++){
        int* a = malloc(sizeof(int));
        *a =i;
		if (i == 4 || i == 5){
			pthread_create(&th[i], NULL, &fuel_filling, a);
		}
		else{
			pthread_create(&th[i], NULL, &car, a);
		}
			
    }

    for (i=0; i<TH_NUM; i++){
        int* r;
        pthread_join(th[i], (void**)&r);
        
    }

	pthread_mutex_destroy(&mutexFuel);
	pthread_cond_destroy(&condFuel);

    return 0;

}