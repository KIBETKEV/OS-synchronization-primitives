// semaphores
// Simulates Producer–Consumer synchronization using semaphores.
// Author: Kelvin Ngeno
// Course: AIT 542 – Fundamentals of Computing Platforms

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

sem_t empty, full;      // Semaphores
pthread_mutex_t mutex;  // Mutex for critical section

void* producer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty);               // Wait if buffer is full
        pthread_mutex_lock(&mutex);     // Enter critical section

        buffer[count++] = i;
        printf("Produced item %d | Buffer count: %d\n", i, count);

        pthread_mutex_unlock(&mutex);   // Exit critical section
        sem_post(&full);                // Signal that buffer has data
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);                // Wait if buffer is empty
        pthread_mutex_lock(&mutex);     // Enter critical section

        int item = buffer[--count];
        printf("Consumed item %d | Buffer count: %d\n", item, count);

        pthread_mutex_unlock(&mutex);   // Exit critical section
        sem_post(&empty);               // Signal that buffer has space
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for both threads to complete
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("\nAll items produced and consumed successfully!\n");
    return 0;
}