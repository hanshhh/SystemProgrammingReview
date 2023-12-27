#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// This will create a segfault since it's on the stack. 
// It would be deallocated.
// void* roll_dice() {
//     int value = (rand() % 6) + 1;
//     printf("%d\n", value);
//     return (void*) &value;
// }

// void* roll_dice(void *arg) {
//     Correct alternative 1: Dynamically allocate memory on heap.
//     int index = (int) arg;
//     int value = (rand() % 6) + 1;
//     int *result = malloc(sizeof(int));
    
//     *result = value;
//     printf("thread %d: %d\n",index, value);
//     return (void*) result;
// }


// int main(int argc, char* argv[]){
//     pthread_t th[6];
//     int* res;


//     int i;
//     for (i = 0; i < 5; i++) {
//         pthread_create(&(th[i]), NULL, &roll_dice, (void *) i);
//     }
    
   

//     for (i = 0; i < 5; i++) {
//         pthread_join(th[i], (void **)(&res));
//         printf("Result %d: %d\n", i, *res);
//         free(res);
//     }


//     return 0;
// }



int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void* routine(void* arg) {
    sleep(1);
    int index = *(int*)arg;
    printf("%d ", primes[index]);
    free(arg);
}

int main(int argc, char* argv[]) {
    pthread_t th[10];
    int i;
    for (i = 0; i < 10; i++) {
        int* a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0) {
            perror("Failed to created thread");
        }
    }
    for (i = 0; i < 10; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    
    return 0;
}