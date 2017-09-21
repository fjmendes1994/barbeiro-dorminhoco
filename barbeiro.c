
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

typedef int semaphore;

semaphore customers = 0;
semaphore barbers = 0;
semaphore painters = 0;
semaphore hairstylist = 0;
semaphore mutex = 1;
int waiting = 0;


void barber(){
    while(1){
        down(&customers);
        down(&mutex);
        waiting = waiting - 1;
        up(&barbers);
        up(&mutex);
        cut_beard();
    }

}

void painter(){
    while(1){
        down(&customers);
    }


}
int main(){
    printf("Olá Barbeiro\n");
    return 0;
}