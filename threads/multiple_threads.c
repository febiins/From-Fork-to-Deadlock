#include<stdio.h>
#include<pthread.h>

void* task(void* args){
    printf("\nMultiple threads");
    return NULL;

}

int main(){
    pthread_t t1,t2;

    pthread_create(&t1,NULL,task,NULL);
    pthread_create(&t2,NULL,task,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("\nMain thread starts");
}