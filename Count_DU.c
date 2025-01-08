#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore_A;
sem_t semaphore_B;

void* print_A(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&semaphore_A);
        printf("Thread A: %d\n", i);
        fflush(stdout);
        sem_post(&semaphore_B);
    }
    return NULL;
}

void* print_B(void* arg) {
    for (int i = 10; i > 0; i--) {
        sem_wait(&semaphore_B);
        printf("Thread B: %d\n", i);
        fflush(stdout);
        sem_post(&semaphore_A);
    }
    return NULL;
}

int main() {
    sem_init(&semaphore_A, 0, 1);
    sem_init(&semaphore_B, 0, 0);

    pthread_t thread_A;
    pthread_t thread_B;

    pthread_create(&thread_A, NULL, print_A, NULL);
    pthread_create(&thread_B, NULL, print_B, NULL);

    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    sem_destroy(&semaphore_A);
    sem_destroy(&semaphore_B);

    return 0;
}
