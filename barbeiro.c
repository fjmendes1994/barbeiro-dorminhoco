// gcc barbeiro.c -o b -pthread
// ./b

#define CHAIRS 5

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t customers_for_paint, customers_for_shave, customers_for_cut, 
      barbers, painters, hairstylists,
      mutex;
    
int waiting = 0;


void shave(){
    printf("Ta feita...\n");
}

void get_shave(){
    printf("To indo fazer a barba hein...\n");
}

void paint(){
    printf("Ta pintado...\n");
}

void get_paint(){
    printf("To indo pintar o cabelo hein...\n");
}

void cut(){
    printf("Ta cortado...\n");
}

void get_cut(){
    printf("To indo cortar o cabelo hein...\n");
}

void barber(){
    while(1){
        sem_wait(&customers_for_shave);
        sem_wait(&mutex);
        waiting = waiting - 1;
        shave();
        sem_post(&barbers);
        sem_post(&mutex);
        
    }
}

void painter(){
    while(1){
        sem_wait(&customers_for_paint);
        sem_wait(&mutex);
        waiting = waiting - 1;
        paint();
        sem_post(&painters);
        sem_post(&mutex);
        
    }
}

void hairstylist(){
    while(1){
        sem_wait(&customers_for_cut);
        sem_wait(&mutex);
        waiting = waiting - 1;
        cut();
        sem_post(&hairstylists);
        sem_post(&mutex);
        
    }
}

void customer_for_shave(){
    sem_wait(&mutex);
    if(waiting < CHAIRS){
        waiting = waiting + 1;
        sem_post(&customers_for_shave);
        get_shave();
        sem_post(&mutex);
        sem_wait(&barbers);
    } else {
        sem_post(&mutex);
        printf("Fila tá cheia. Até mais.\n");
    }
}

void customer_for_paint(){
    sem_wait(&mutex);
    if(waiting < CHAIRS){
        waiting = waiting + 1;
        sem_post(&customers_for_paint);
        get_paint();
        sem_post(&mutex);
        sem_wait(&painters);
    } else {
        sem_post(&mutex);
        printf("Fila tá cheia. Até mais.\n");
    }
}

void customer_for_cut(){
    sem_wait(&mutex);
    if(waiting < CHAIRS){
        waiting = waiting + 1;
        sem_post(&customers_for_cut);
        get_cut();
        sem_post(&mutex);
        sem_wait(&hairstylists);
    } else {
        sem_post(&mutex);
        printf("Fila tá cheia. Até mais.\n");
    }
}

int main(){

    sem_init(&customers_for_shave, 0, 0);
    sem_init(&customers_for_paint, 0, 0);
    sem_init(&customers_for_cut, 0, 0);
    sem_init(&barbers, 0, 0);
    sem_init(&painters, 0, 0);
    sem_init(&hairstylists, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t b, p, h, cs, cp, cc;

    pthread_create(&b, NULL, (void*)barber, NULL);
    pthread_create(&p, NULL, (void*)painter, NULL);
    pthread_create(&h, NULL, (void*)hairstylist, NULL);

    while(1) {
        pthread_create(&cs, NULL, (void *) customer_for_shave, NULL);
        pthread_create(&cp, NULL, (void *) customer_for_paint, NULL);
        pthread_create(&cc, NULL, (void *) customer_for_cut, NULL);
        sleep(0.7);
    }

    return 0;
}