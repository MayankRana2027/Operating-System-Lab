#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];
pthread_t philosopher[N];
int phil_num[N] = {0, 1, 2, 3, 4};

void* dine(void* num) {
    int i = *(int*)num;
    while (1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);
        sem_wait(&chopstick[i]);
        sem_wait(&chopstick[(i + 1) % N]);
        printf("Philosopher %d is eating\n", i);
        sleep(1);
        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i + 1) % N]);
    }
}

int main() {
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);
    for (int i = 0; i < N; i++)
        pthread_create(&philosopher[i], NULL, dine, &phil_num[i]);
    for (int i = 0; i < N; i++)
        pthread_join(philosopher[i], NULL);
    for (int i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);
    return 0;
}
