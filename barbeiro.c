// https://github.com/silasss/theSleepingBarberProblem/blob/master/main.c
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
    printf("Ta feita...");
}

void get_shave(){
    printf("To indo fazer a barba hein...");
}

void paint(){
    printf("Ta feita...");
}

void get_paint(){
    printf("To indo fazer a barba hein...");
}

void cut(){
    printf("Ta feita...");
}

void get_cut(){
    printf("To indo fazer a barba hein...");
}

void barber(){
    while(1){
        sem_wait(&customers_for_shave);
        sem_wait(&mutex);
        waiting = waiting - 1;
        sem_post(&barbers);
        sem_post(&mutex);
        shave();
    }
}

void painter(){
    while(1){
        sem_wait(&customers_for_paint);
        sem_wait(&mutex);
        waiting = waiting - 1;
        sem_post(&painters);
        sem_post(&mutex);
        paint();
    }
}

void hairstylist(){
    while(1){
        sem_wait(&customers_for_cut);
        sem_wait(&mutex);
        waiting = waiting - 1;
        sem_post(&hairstylists);
        sem_post(&mutex);
        cut();
    }
}

void customer_for_shave(){
    sem_wait(&mutex);
    if(waiting < CHAIRS){
        waiting = waiting + 1;
        sem_post(&customers_for_shave);
        sem_post(&mutex);
        sem_wait(&barbers);
        get_shave();
    } else {
        sem_post(&mutex);
    }
}

void customer_for_paint(){
    sem_wait(&mutex);
    if(waiting < CHAIRS){
        waiting = waiting + 1;
        sem_post(&customers_for_paint);
        sem_post(&mutex);
        sem_wait(&painters);
        get_paint();
    } else {
        sem_post(&mutex);
    }
}

void customer_for_cut(){
    sem_wait(&mutex);
    if(waiting < CHAIRS){
        waiting = waiting + 1;
        sem_post(&customers_for_cut);
        sem_post(&mutex);
        sem_wait(&hairstylists);
        get_cut();
    } else {
        sem_post(&mutex);
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
    printf("Olá Barbeiro\n");
    return 0;
}