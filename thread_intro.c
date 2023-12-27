#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine() {
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
}

// gcc -g -pthread <filename.c> -o <filename>
int main(int argc, char* argv[]){
    pthread_t t1;
    pthread_t t2;
    // Create a thread
    // 
    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);
    // Main thread wait for this worker thread t1.
    // second arg is the result from the thread.
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}