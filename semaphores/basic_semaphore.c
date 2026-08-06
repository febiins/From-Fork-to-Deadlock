#include <stdio.h>          // printf()
#include <pthread.h>        // Thread functions
#include <semaphore.h>      // Semaphore functions
#include <unistd.h>         // sleep()

// Global semaphore
// Shared by all threads
sem_t semaphore;

// Thread function executed by every thread
void* worker(void* arg)
{
    // Get the thread ID passed from main()
    int id = *(int*)arg;

    // Thread requests access to the critical section
    printf("Thread %d wants to enter\n", id);

    // Decrease semaphore value.
    //
    // If semaphore > 0:
    //      Decrease its value and allow the thread to enter.
    //
    // If semaphore == 0:
    //      The thread waits until another thread
    //      calls sem_post().
    sem_wait(&semaphore);

    // Critical Section
    printf(">>> Thread %d ENTERED Critical Section\n", id);

    // Simulate some work inside the critical section
    sleep(5);

    // Thread finished its work
    printf("<<< Thread %d LEFT Critical Section\n", id);

    // Increase semaphore value.
    // If any thread is waiting,
    // one waiting thread is allowed to continue.
    sem_post(&semaphore);

    return NULL;
}

int main()
{
    // Three thread variables
    pthread_t t1, t2, t3;

    // IDs passed to each thread
    int id1 = 1;
    int id2 = 2;
    int id3 = 3;

    /*
        sem_init(&semaphore, 0, 1);

        &semaphore -> Semaphore variable
        0          -> Shared between threads
        1          -> Initial semaphore value

        Since the value is 1,
        ONLY ONE thread can enter the
        critical section at a time.

        Thread 2 and Thread 3 must wait
        until Thread 1 calls sem_post().
    */

    sem_init(&semaphore, 0, 1);

    // Create three threads
    pthread_create(&t1, NULL, worker, &id1);
    sleep(2);
    pthread_create(&t2, NULL, worker, &id2);
    sleep(2);
    pthread_create(&t3, NULL, worker, &id3);

    // Wait until all threads finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}

/*
=========================================================
SUGGESTION

Try changing

sem_init(&semaphore, 0, 1);

to

sem_init(&semaphore, 0, 3);

What happens?

Semaphore Value = 3

↓

Three resources are available.

Execution

Thread 1
sem_wait()

Semaphore
3 → 2

Thread 1 ENTERS

------------------------------------

Thread 2
sem_wait()

Semaphore
2 → 1

Thread 2 ENTERS

------------------------------------

Thread 3
sem_wait()

Semaphore
1 → 0

Thread 3 ENTERS

------------------------------------

Notice:

All three threads execute the
critical section simultaneously.

No thread waits because the semaphore
initially allowed three entries.

---------------------------------------------------------

To clearly observe a counting semaphore,

Create FIVE threads instead of THREE.

Semaphore = 3

Thread 1 → ENTER

Thread 2 → ENTER

Thread 3 → ENTER

Thread 4 → WAIT

Thread 5 → WAIT

When any one thread calls sem_post(),

↓

One waiting thread wakes up
and enters the critical section.

This demonstrates the real purpose of
a counting semaphore.

=========================================================
*/