
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Number of readers currently reading
int read_count = 0;

// Protects read_count
pthread_mutex_t mutex;

// Controls access to the shared resource
sem_t writeLock;

// ---------------- READER ----------------
void* reader(void* arg)
{
    int id = *(int*)arg;

    // Protect read_count
    pthread_mutex_lock(&mutex);

    read_count++;

    // First reader blocks writers
    if(read_count == 1)
    {
        sem_wait(&writeLock);
    }

    pthread_mutex_unlock(&mutex);

    // Multiple readers can execute this simultaneously
    printf("Reader %d is reading...\n", id);
    sleep(2);

    // Reader has finished
    pthread_mutex_lock(&mutex);

    read_count--;

    // Last reader allows writers
    if(read_count == 0)
    {
        sem_post(&writeLock);
    }

    pthread_mutex_unlock(&mutex);

    printf("Reader %d finished reading.\n", id);

    return NULL;
}

// ---------------- WRITER ----------------
void* writer(void* arg)
{
    int id = *(int*)arg;

    // Wait until no readers or writers are accessing
    sem_wait(&writeLock);

    printf("Writer %d is writing...\n", id);
    sleep(3);

    printf("Writer %d finished writing.\n", id);

    // Allow next reader or writer
    sem_post(&writeLock);

    return NULL;
}

// ---------------- MAIN ----------------
int main()
{
    pthread_t r1, r2, r3, w1;

    int reader1 = 1, reader2 = 2, reader3 = 3;
    int writer1 = 1;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&writeLock, 0, 1);

    pthread_create(&r1, NULL, reader, &reader1);
    sleep(1);

    pthread_create(&r2, NULL, reader, &reader2);
    sleep(1);

    pthread_create(&r3, NULL, reader, &reader3);
    sleep(1);

    pthread_create(&w1, NULL, writer, &writer1);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w1, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&writeLock);

    return 0;
}