#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];

// Philosopher function
void* philosopher(void* arg)
{
    int id = *(int*)arg;

    int left = id;
    int right = (id + 1) % N;

    printf("Philosopher %d is thinking\n", id + 1);

    // Pick up left fork
    pthread_mutex_lock(&forks[left]);
    printf("Philosopher %d picked left fork\n", id + 1);

    // Pick up right fork
    pthread_mutex_lock(&forks[right]);
    printf("Philosopher %d picked right fork\n", id + 1);

    // Eat
    printf("Philosopher %d is eating\n", id + 1);
    sleep(2);

    // Release forks
    pthread_mutex_unlock(&forks[left]);
    pthread_mutex_unlock(&forks[right]);

    printf("Philosopher %d finished eating\n", id + 1);

    return NULL;
}

int main()
{
    pthread_t threads[N];
    int ids[N];

    // Initialize forks
    for(int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);

    // Create and execute philosophers sequentially
    for(int i = 0; i < N; i++)
    {
        ids[i] = i;

        pthread_create(&threads[i], NULL, philosopher, &ids[i]);

        // Wait for current philosopher to finish
        pthread_join(threads[i], NULL);
    }

    // Destroy forks
    for(int i = 0; i < N; i++)
        pthread_mutex_destroy(&forks[i]);

    return 0;
}