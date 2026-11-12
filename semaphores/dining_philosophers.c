
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

// Five forks represented using mutexes
pthread_mutex_t forks[N];

// Philosopher function
void* philosopher(void* arg)
{
    int id = *(int*)arg;

    // Calculate left and right fork numbers
    int left = id;
    int right = (id + 1) % N;

    printf("Philosopher %d is thinking...\n", id + 1);
    sleep(1);

    // Pick up left fork
    pthread_mutex_lock(&forks[left]);
    printf("Philosopher %d picked up left fork\n", id + 1);

    // Pick up right fork
    pthread_mutex_lock(&forks[right]);
    printf("Philosopher %d picked up right fork\n", id + 1);

    // Eat
    printf("Philosopher %d is eating...\n", id + 1);
    sleep(2);

    // Release both forks
    pthread_mutex_unlock(&forks[left]);
    pthread_mutex_unlock(&forks[right]);

    printf("Philosopher %d finished eating\n", id + 1);

    return NULL;
}

int main()
{
    pthread_t threads[N];
    int ids[N];

    // Initialize all five forks
    for(int i = 0; i < N; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create five philosopher threads
    for(int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // Wait for philosophers
    for(int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destroy all forks
    for(int i = 0; i < N; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
