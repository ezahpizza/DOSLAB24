#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_A;
sem_t sem_B;
sem_t sem_C;
int counter = 1;

void* print_sequence_A(void* arg) {
    for (int i = 0; i < 7; i++) {
        sem_wait(&sem_A);
        printf("A%d\n", counter);
        counter++;
        sem_post(&sem_B);
    }
    return NULL;
}

void* print_sequence_B(void* arg) {
    for (int i = 0; i < 7; i++) {
        sem_wait(&sem_B);
        printf("B%d\n", counter);
        counter++;
        sem_post(&sem_C);
    }
    return NULL;
}

void* print_sequence_C(void* arg) {
    for (int i = 0; i < 7; i++) {
        sem_wait(&sem_C);
        printf("C%d\n", counter);
        counter++;
        sem_post(&sem_A);
    }
    return NULL;
}

int main() {
    sem_init(&sem_A, 0, 1);
    sem_init(&sem_B, 0, 0);
    sem_init(&sem_C, 0, 0);

    pthread_t thread_A, thread_B, thread_C;

    pthread_create(&thread_A, NULL, print_sequence_A, NULL);
    pthread_create(&thread_B, NULL, print_sequence_B, NULL);
    pthread_create(&thread_C, NULL, print_sequence_C, NULL);

    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);
    pthread_join(thread_C, NULL);

    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    sem_destroy(&sem_C);

    return 0;
}
