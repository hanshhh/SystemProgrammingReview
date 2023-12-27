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

void* roll_dice(void *arg) {
    // Correct alternative 1: Dynamically allocate memory on heap.
    int index = (int) arg;
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    
    *result = value;
    printf("thread %d: %d\n",index, value);
    return (void*) result;
}

// gcc -g -pthread <filename.c> -o <filename>
int main(int argc, char* argv[]){
    pthread_t th[6];
    int* res;

    // Create a thread
    // 
    int i;
    for (i = 0; i < 5; i++) {
        pthread_create(&(th[i]), NULL, &roll_dice, (void *) i);
    }
    
   
    // Main thread wait for this worker thread t1.
    // second arg is the result from the thread.
    for (i = 0; i < 5; i++) {
        pthread_join(th[i], (void **)(&res));
        printf("Result %d: %d\n", i, *res);
        free(res);
    }
    // pthread_join(t1, (void **)(&res));
    // printf("Result: %d/n", *res);

    

    return 0;
}