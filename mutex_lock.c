#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for (int i = 0; i < 10000000; i++) {
        // mutual exclusion using lock and unlock for the critical section
        // This prevents race_condition from happening. 
        // Protection over the shared memory.
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char* argv[]) {
    pthread_t th[8];
    int i;
    int rc = pthread_mutex_init(&mutex, NULL);
    assert(rc == 0); // always check success!
    for (i = 0; i < 8; i++) {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 8; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}

// void *mythread(void *arg) {
//     long long int value = (long long int) arg;
//     printf("%lld\n", value);
//     return (void *) (value + 1);
// }
// int main(int argc, char *argv[]) {
//     pthread_t p;
//     long long int rvalue;
//     Pthread_create(&p, NULL, mythread, (void *) 100);
//     Pthread_join(p, (void **) &rvalue);
//     printf("returned %lld\n", rvalue);
//     return 0;
// }