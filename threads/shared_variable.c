#include<stdio.h>
#include<pthread.h>

int counter=0;

void* increment(void* args){
    printf("\nThread has started");

    counter++;

    printf("Thread Counter = %d\n", counter);

    return NULL;
}

int main(){
    pthread_t t1;

    printf("Before Thread Counter = %d\n", counter);
    pthread_create(&t1, NULL, increment, NULL);

    pthread_join(t1, NULL);

    printf("After Thread Counter = %d\n", counter);

    return 0;
}

/*
================================================

SHARED VARIABLE DEMO

Initially

Process

Global Variable
---------------
counter = 0


pthread_create()

             Process

      Main Thread
            |
            |
      Thread T1


Both threads access the
same global variable.

Thread executes

counter++;

Global Memory

counter = 1

Main thread also sees

counter = 1

because threads share
the same process memory.

Important

Processes
    Separate Memory

Threads
    Shared Memory

================================================
*/