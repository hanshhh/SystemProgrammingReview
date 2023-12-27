#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg) {
    sleep(1);
    int index = *(int*)arg;
    int sum = 0;
    for (int i = 0; i < 5; i ++) {
        sum += primes[index + i];
    }
    free(arg);
    int *result = malloc(sizeof(int));
    *result = sum;
    printf("Local Sum from worker thread: %d\n", sum);
    return (void *) result;
}

int main(int argc, char* argv[]) {
    int sum = 0;
    pthread_t th[2];
    int i;
    for (i = 0; i < 2; i++) {
        int* a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to created thread");
        }
    }
    for (i = 0; i < 2; i++) {
        int *r;
        if (pthread_join(th[i], &r) != 0) {
            perror("Failed to join thread");
        }
        sum += *r;
        free(r);
    }
    printf("Sum of the array using two threads is %d\n", sum);
    
    return 0;
}