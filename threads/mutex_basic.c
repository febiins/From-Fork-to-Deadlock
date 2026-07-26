#include<stdio.h>
#include<pthread.h>

int counter=0;
pthread_mutex_t lock;//created mutex
void* increment(void* args){

    /* Lock the critical section */
    pthread_mutex_lock(&lock);
    for(int i = 0; i < 100000; i++)
    {
        counter++;
    }

    printf("Thread finished. Counter = %d\n", counter);

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(){
    pthread_t t1,t2;

    /* Initialize mutex */
    pthread_mutex_init(&lock,NULL);
    pthread_create(&t1,NULL,increment,NULL);
    pthread_create(&t2,NULL,increment,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("Final Counter = %d\n", counter);
    /* Destroy mutex */
    pthread_mutex_destroy(&lock);
    return 0;
}

/*
===========================================================
                    MUTEX (Mutual Exclusion)
===========================================================

Definition

A Mutex is a synchronization mechanism that allows
ONLY ONE thread to access a shared resource at a time.

Purpose

To prevent Race Conditions when multiple threads
access the same shared variable.

-----------------------------------------------------------

Without Mutex

Shared Variable

             counter = 0

                 ▲
                 |
        -------------------
        |                 |
    Thread 1          Thread 2

Both threads execute

counter++;

at the same time.

Example

counter = 5

Thread 1              Thread 2

Read 5                Read 5
Add 1                 Add 1
Write 6               Write 6

Expected Counter = 7
Actual Counter   = 6

One increment is lost.

This problem is called

        RACE CONDITION

-----------------------------------------------------------

With Mutex

Initially

Mutex = Unlocked

Thread 1 executes

pthread_mutex_lock(&lock);

Mutex becomes Locked.

                Thread 1
                   |
                   V
            Critical Section

               counter++;

Thread 2 also executes

pthread_mutex_lock(&lock);

But the mutex is already locked.

Thread 2 cannot enter the
critical section.

It waits until Thread 1 finishes.

-----------------------------------------------------------

Thread 1 finishes its work.

pthread_mutex_unlock(&lock);

Mutex becomes Unlocked.

Now Thread 2 acquires the lock.

                Thread 2
                   |
                   V
            Critical Section

               counter++;

After finishing,

Thread 2 unlocks the mutex.

-----------------------------------------------------------

Execution Flow

                Main Thread

                     |
                     V

           Create Thread 1
           Create Thread 2

                     |
                     V

          Thread 1 locks Mutex

                     |
                     V

         Access Shared Variable

              counter++

                     |
                     V

         Thread 1 unlocks Mutex

                     |
                     V

          Thread 2 locks Mutex

                     |
                     V

         Access Shared Variable

              counter++

                     |
                     V

         Thread 2 unlocks Mutex

                     |
                     V

          Main Thread prints

           Counter = 200000

-----------------------------------------------------------

Memory View

                 PROCESS

        +-----------------------+
        |  Global Variable      |
        |                       |
        |   counter             |
        +-----------------------+
                  ▲
                  |
             Mutex Lock
                  |
        ---------------------
        |                   |
    Thread 1           Thread 2

If Thread 1 has the mutex,

↓

Thread 2 must wait.

Only one thread can access
the shared variable at a time.

-----------------------------------------------------------

Important Functions

pthread_mutex_t lock;
    Creates a mutex variable.

pthread_mutex_init(&lock, NULL);
    Initializes the mutex.

pthread_mutex_lock(&lock);
    Locks the mutex before entering
    the critical section.

pthread_mutex_unlock(&lock);
    Unlocks the mutex after leaving
    the critical section.

pthread_mutex_destroy(&lock);
    Destroys the mutex when it is
    no longer needed.

-----------------------------------------------------------

Key Points

✔ Mutex = Mutual Exclusion

✔ Used to protect shared resources.

✔ Only one thread can execute the
  critical section at a time.

✔ Prevents race conditions.

✔ Always lock before accessing
  shared data.

✔ Always unlock after finishing.

===========================================================
*/