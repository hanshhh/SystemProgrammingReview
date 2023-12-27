#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int fuel = 0;
pthread_mutex_t mutexFuel;

void * fuel_filling(void *arg) {

}

void *car(void *arg){

}

int main(int argc, char* argv[]) {
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    for (int i = 0; i < 2; i ++) {
        if (i == 0) {
            if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0) {
                perror("Failed to create thread");
                exit(1);
            }
        } else {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0) {
                perror("Failed to create thread");
                exit(1);
            }
        }
    }
    for (int i = 0; i < 2; i ++) {
        if (pthread_join(th[i], NULL)!= 0) {
            perror("Failed to join thread");
        }
    }
    pthread_mutex_destroy(&mutexFuel);
    return 0;
}