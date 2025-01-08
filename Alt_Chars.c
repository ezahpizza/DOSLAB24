#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_COUNT 20

sem_t semA, semB;

void* printA(void* arg) {
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&semA); // Wait for semaphore A
        printf("A");
        fflush(stdout); // Ensure output is printed immediately
        sem_post(&semB); // Signal semaphore B
    }
    return NULL;
}

void* printB(void* arg) {
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&semB); // Wait for semaphore B
        printf("B");
        fflush(stdout); // Ensure output is printed immediately
        sem_post(&semA); // Signal semaphore A
    }
    return NULL;
}

int main() {
    pthread_t threadA, threadB;

    // Initialize semaphores
    sem_init(&semA, 0, 1); // Semaphore A starts unlocked
    sem_init(&semB, 0, 0); // Semaphore B starts locked

    // Create threads
    pthread_create(&threadA, NULL, printA, NULL);
    pthread_create(&threadB, NULL, printB, NULL);

    // Wait for threads to finish
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    // Destroy semaphores
    sem_destroy(&semA);
    sem_destroy(&semB);

    printf("\n"); // New line after output

    return 0;
}
