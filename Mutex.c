// mutex
// Demonstrates mutual exclusion using pthread mutex locks.
// Author: Kelvin Ngeno
// Course: AIT 542 – Fundamentals of Computing Platforms

#include <stdio.h>
#include <pthread.h>

int counter = 0;                 // Shared resource
pthread_mutex_t lock;            // Mutex variable

void* increment(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);           // Enter critical section
        int id = *(int*)arg;
        printf("Thread %d entering critical section\n", id);
        counter++;
        printf("Thread %d incremented counter to %d\n", id, counter);
        printf("Thread %d leaving critical section\n\n", id);
        pthread_mutex_unlock(&lock);         // Exit critical section
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create two threads
    pthread_create(&t1, NULL, increment, &id1);
    pthread_create(&t2, NULL, increment, &id2);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);
    return 0;
}