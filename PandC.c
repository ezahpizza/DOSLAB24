#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;
sem_t empty, full, mutex;

void *producer(void *param) {
    int item;
    for (int i = 0; i < 20; i++) {
        item = rand() % 100; // Produce an item
        printf("Producer: waiting on empty...\n");
        sem_wait(&empty);
        printf("Producer: acquired mutex...\n");
        sem_wait(&mutex);

        buffer[count++] = item; // Add item to the buffer
        printf("Producer produced %d\n", item);

        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *param) {
    int item;
    for (int i = 0; i < 20; i++) {
        printf("Consumer: waiting on full...\n");
        sem_wait(&full);
        printf("Consumer: acquired mutex...\n");
        sem_wait(&mutex);

        item = buffer[--count]; // Remove item from the buffer
        printf("Consumer consumed %d\n", item);

        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Disable buffering for immediate output
    setvbuf(stdout, NULL, _IONBF, 0);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
