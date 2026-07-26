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