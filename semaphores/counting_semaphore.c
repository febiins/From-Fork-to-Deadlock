#include <stdio.h>          // printf()
#include <pthread.h>        // Thread functions
#include <semaphore.h>      // Semaphore functions
#include <unistd.h>         // sleep()

// Global Counting Semaphore
// Shared by all threads
sem_t semaphore;

// Thread function
void* worker(void* args)
{
    // Receive thread ID from main()
    int id = *(int*) args;

    // Thread requests access to the Critical Section
    printf("Thread %d wants to enter the Critical Section.\n", id);

    /*
        sem_wait()

        Decreases semaphore value by 1.

        If semaphore > 0
            Thread enters Critical Section.

        If semaphore == 0
            Thread waits until another
            thread calls sem_post().
    */
    sem_wait(&semaphore);

    // Thread entered Critical Section
    printf(">>> Thread %d ENTERED Critical Section.\n", id);

    // Simulate work for 3 seconds
    sleep(3);

    // Thread completed its work
    printf("<<< Thread %d LEFT Critical Section.\n", id);

    /*
        sem_post()

        Increases semaphore value by 1.

        If any thread is waiting,
        one waiting thread is allowed
        to enter the Critical Section.
    */
    sem_post(&semaphore);

    return NULL;
}

int main()
{
    // Five thread variables
    pthread_t t1, t2, t3, t4, t5;

    // Thread IDs
    int id1, id2, id3, id4, id5;

    id1 = 1;
    id2 = 2;
    id3 = 3;
    id4 = 4;
    id5 = 5;

    /*
        Initialize Counting Semaphore

        &semaphore -> Semaphore variable

        0 -> Shared between threads
             of the same process.

        3 -> Initial semaphore value.

        Meaning:
        Three threads can enter the
        Critical Section simultaneously.
    */
    sem_init(&semaphore, 0, 3);

    // Create Thread 1
    pthread_create(&t1, NULL, worker, &id1);

    // Delay so output becomes easier to observe
    sleep(2);

    // Create Thread 2
    pthread_create(&t2, NULL, worker, &id2);

    sleep(2);

    // Create Thread 3
    pthread_create(&t3, NULL, worker, &id3);

    sleep(2);

    // Create Thread 4
    pthread_create(&t4, NULL, worker, &id4);

    sleep(2);

    // Create Thread 5
    pthread_create(&t5, NULL, worker, &id5);

    // Main waits until every thread finishes
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}

/*

                    Program Starts

                           |

                           V

               sem_init(&semaphore,0,3)

               Semaphore Value = 3

                           |

                           V

              Create Thread 1

                           |

Thread 1

sem_wait()

Semaphore

3 → 2

ENTER

-------------------------------------------------

After 2 seconds

Create Thread 2

Thread 2

sem_wait()

Semaphore

2 → 1

ENTER

-------------------------------------------------

After 2 seconds

Create Thread 3

Thread 3

sem_wait()

Semaphore

1 → 0

ENTER

-------------------------------------------------

After 2 seconds

Create Thread 4

Thread 4

sem_wait()

Semaphore = 0

WAITING

-------------------------------------------------

Thread 1 finishes

sem_post()

Semaphore

0 → 1

↓

Thread 4 wakes up

↓

Thread 4 ENTERS

-------------------------------------------------

Create Thread 5

Thread 5

sem_wait()

Semaphore = 0

WAITING

-------------------------------------------------

Thread 2 finishes

sem_post()

Semaphore

0 → 1

↓

Thread 5 wakes up

↓

Thread 5 ENTERS

-------------------------------------------------

All Threads Finish

↓

Main Thread continues

↓

sem_destroy()

↓

Program Ends



*/