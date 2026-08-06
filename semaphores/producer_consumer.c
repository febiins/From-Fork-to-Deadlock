
// Note: Reduce the producer's sleep time to 1 second to better understand the synchronization between the producer and consumer.After the initial execution only.

#include <stdio.h>          // printf()
#include <pthread.h>        // Thread library
#include <semaphore.h>      // Semaphore functions
#include <unistd.h>         // sleep()

// Buffer can store only 5 items at a time
#define BUFFER_SIZE 5

// Shared Buffer
int buffer[BUFFER_SIZE];

// Number of items currently stored in the buffer
int count = 0;

// Semaphore that counts produced items
sem_t full;

// Semaphore that counts empty slots
sem_t empty;

// Mutex protects the shared buffer and count variable
pthread_mutex_t mutex;

// Producer Thread
void* produce(void* args)
{
    // Item starts from 1
    int item = 1;

    // Produce 10 items
    while(item <= 10)
    {
        /*
            Wait until an empty slot is available.

            empty--

            If empty == 0,
            Producer waits.
        */
        sem_wait(&empty);

        /*
            Lock the buffer.

            Producer gets exclusive access
            to buffer[] and count.
        */
        pthread_mutex_lock(&mutex);

        // Store item inside the buffer
        buffer[count] = item;

        printf("Produced : %d\n", item);

        // One more item is available
        count++;

        /*
            Unlock the buffer.

            Consumer can now access it.
        */
        pthread_mutex_unlock(&mutex);

        /*
            Increase full semaphore.

            full++

            One more produced item
            is available.
        */
        sem_post(&full);

        // Produce next item
        item++;

        // Slow down execution
        sleep(2);
    }

    return NULL;
}

// Consumer Thread
void* consume(void* args)
{
    int item;

    while(1)
    {
        /*
            Wait until a produced item exists.

            full--

            If full == 0,
            Consumer waits.
        */
        sem_wait(&full);

        /*
            Lock the buffer.

            Producer cannot modify the
            buffer until Consumer finishes.
        */
        pthread_mutex_lock(&mutex);

        // Remove last produced item
        count--;

        item = buffer[count];

        printf("Consumed : %d\n", item);

        /*
            Unlock buffer.
        */
        pthread_mutex_unlock(&mutex);

        /*
            Increase empty semaphore.

            empty++

            One buffer slot becomes free.
        */
        sem_post(&empty);

        sleep(2);
    }

    return NULL;
}

int main()
{
    // Producer thread
    pthread_t producer;

    // Consumer thread
    pthread_t consumer;

    /*
        Initialize empty semaphore.

        Buffer Size = 5

        Initially

        Empty Slots = 5
    */
    sem_init(&empty, 0, BUFFER_SIZE);

    /*
        Initialize full semaphore.

        Initially

        No items are produced.

        Full = 0
    */
    sem_init(&full, 0, 0);

    /*
        Initialize Mutex.

        Used to protect

        buffer[]

        and

        count
    */
    pthread_mutex_init(&mutex, NULL);

    // Create Producer Thread
    pthread_create(&producer, NULL, produce, NULL);

    // Create Consumer Thread
    pthread_create(&consumer, NULL, consume, NULL);

    // Wait until Producer finishes
    pthread_join(producer, NULL);

    /*
    The consumer runs inside an infinite loop (while(1)),
    so it never terminates on its own.

    After the producer finishes producing all items,
    the main thread cancels the consumer thread to
    allow the program to terminate.
    */
    pthread_cancel(consumer);

    // Destroy Mutex
    pthread_mutex_destroy(&mutex);

    // Destroy Semaphores
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

/*

===========================================================
            PRODUCER - CONSUMER (BASIC)
===========================================================

Definition

The Producer creates data.

The Consumer reads data.

Both share the same buffer.

-----------------------------------------------------------

Shared Buffer

+----+----+----+----+----+
|    |    |    |    |    |
+----+----+----+----+----+

count = 0

-----------------------------------------------------------

Synchronization Objects

empty

↓

Counts Empty Slots.

Initially

Empty = 5

-----------------------------------------------------------

full

↓

Counts Produced Items.

Initially

Full = 0

-----------------------------------------------------------

mutex

↓

Protects

buffer[]

count

Only one thread may modify them
at a time.

-----------------------------------------------------------

Producer Flow

Producer

↓

sem_wait(empty)

↓

Lock Mutex

↓

Store Item

↓

count++

↓

Unlock Mutex

↓

sem_post(full)

-----------------------------------------------------------

Consumer Flow

Consumer

↓

sem_wait(full)

↓

Lock Mutex

↓

count--

↓

Read Item

↓

Unlock Mutex

↓

sem_post(empty)

-----------------------------------------------------------

Execution

Initially

Buffer

+----+----+----+----+----+
|    |    |    |    |    |
+----+----+----+----+----+

Empty = 5

Full = 0

-----------------------------------------------------------

Producer creates Item 1

Empty

5 → 4

↓

Store Item

↓

count = 1

↓

Full

0 → 1

-----------------------------------------------------------

Consumer consumes Item 1

Full

1 → 0

↓

count = 0

↓

Empty

4 → 5

-----------------------------------------------------------

Purpose of Synchronization

empty

↓

Stops Producer when
Buffer is Full.

-----------------------------------------------------------

full

↓

Stops Consumer when
Buffer is Empty.

-----------------------------------------------------------

mutex

↓

Prevents Producer and Consumer
from modifying

buffer[]

count

at the same time.

This avoids Race Conditions.

===========================================================

*/

