#include<stdio.h>
#include<pthread.h>

int counter=0;
void* condition(void* args){
    printf("\nThread trying to access the global variable");
      for(int i = 0; i < 100000; i++)
    {
        counter++;
    }
    printf("\nThread Counter = %d\n", counter);
    return NULL;
}

int main(){
    pthread_t t1,t2;

    pthread_create(&t1,NULL,condition,NULL);
    pthread_create(&t2,NULL,condition,NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nCounter = %d\n", counter);

    return 0;
}

/*
=========================================================
RACE CONDITION - VISUAL EXPLANATION
=========================================================

Initially:

                PROCESS MEMORY

            +----------------+
            | counter = 0    |
            +----------------+

                 ▲      ▲
                 |      |
             Thread1  Thread2


Main Thread creates both threads
and then waits using pthread_join().


---------------------------------------------------------
Both threads execute:

counter++;

Both threads are updating the SAME global variable.

There is NOT a separate counter for each thread.


Example execution:

Shared Counter = 0

        |
        V

Thread1 increments
Thread2 increments
Thread1 increments
Thread2 increments
...

Shared Counter = 37890


---------------------------------------------------------
Thread 1 finishes first.

It executes:

printf("Thread Counter = %d", counter);

Output:

Thread Counter = 37890

This DOES NOT mean Thread1 owns 37890.

It simply prints the CURRENT VALUE of the
shared global variable at that moment.


---------------------------------------------------------
Thread 2 is still running.

It continues incrementing the SAME counter.

Eventually,

Shared Counter = 100000

Thread2 prints:

Thread Counter = 100000


---------------------------------------------------------
Now both threads finish.

pthread_join() returns.

Main Thread resumes.

Main executes:

printf("Counter = %d", counter);

Since the shared counter is now 100000,

Output:

Counter = 100000


---------------------------------------------------------
IMPORTANT

There is only ONE counter.

                counter

                   ▲
          -----------------
          |               |
      Thread1         Thread2

Both threads modify the SAME variable.

Main Thread also reads the SAME variable.

Main is NOT reading Thread1's value or
Thread2's value.

It simply reads the FINAL VALUE stored in
the shared global variable after both
threads have finished.

Because counter++ is not atomic,
many increments are lost.

This problem is called:

            RACE CONDITION

=========================================================
*/