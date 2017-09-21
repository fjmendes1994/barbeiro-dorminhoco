#define CHAIRS 5

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t customers, barbers,
      painters, hairstylist,
      mutex;
    
int waiting = 0;


void shave(){
    printf("Ta feita...");
}

void get_shave(){
    printf("To indo fazer a barba hein...");
}

void barber(){
    while(1){
        sem_wait(&customers);
        sem_wait(&mutex);
        waiting = waiting - 1;
        sem_post(&barbers);
        sem_post(&mutex);
        shave();
    }

}

void customer(){
    sem_wait(&mutex);
    if(waiting < CHAIRS){
        waiting = waiting + 1;
        sem_post(&customers);
        sem_post(&mutex);
        sem_wait(&barbers);
        get_shave();
    } else {
        sem_post(&mutex);
    }
}

int main(){

    sem_init(&customers, 0, 0);
    sem_init(&barbers, 0, 0);
    sem_init(&painters, 0, 0);
    sem_init(&hairstylist, 0, 0);
    sem_init(&mutex, 0, 1);
    printf("Olá Barbeiro\n");
    return 0;
}