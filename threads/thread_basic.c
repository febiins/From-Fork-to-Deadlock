#include<stdio.h>
#include<pthread.h>

void* greet(void* args){
    printf("\nThread is working");

    return NULL;
}

int main(){
    pthread_t t1;
        /*
    Creates a new thread.

    Syntax:

    pthread_create(
        &thread_id,
        attributes,
        function_name,
        argument
    );
    */
    pthread_create(&t1,NULL,greet,NULL);

    pthread_join(t1,NULL);

    printf("\nMain function is working");

    return 0;
}