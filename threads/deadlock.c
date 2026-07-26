#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* thread1(void* args){
    pthread_mutex_lock(&lock1);
    printf("\nThread 1 locked Lock1");
    sleep(1);

    pthread_mutex_lock(&lock2);
    printf("\nThread 1 locked Lock2");
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    return NULL;
}

void* thread2(void* arg)
{
    pthread_mutex_lock(&lock2);
    printf("\nThread 2 locked Lock2\n");

    sleep(1);

    pthread_mutex_lock(&lock1);
    printf("\nThread 2 locked Lock1\n");

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}

/*
==========================================================

DEADLOCK

Definition

A deadlock occurs when two or more threads
wait for each other forever, and none of
them can continue execution.

Execution

Thread 1

Lock Lock1

↓

Needs Lock2

↓

Waiting...

---------------------------------------

Thread 2

Lock Lock2

↓

Needs Lock1

↓

Waiting...

---------------------------------------

Current State

Lock1 -> Held by Thread 1

Lock2 -> Held by Thread 2

Thread 1 waits for Lock2.

Thread 2 waits for Lock1.

Neither thread releases its lock.

Program hangs forever.

This situation is called

            DEADLOCK

==========================================================
*/