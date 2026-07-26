#include<stdio.h>
#include<pthread.h>

void* calculate(void* args){
    static int result = 100;    
    printf("Thread is calculating...\n");
    return &result;
}

int main(){
    pthread_t t1;
    void *res;
    pthread_create(&t1,NULL,calculate,NULL);

    pthread_join(t1, &res);

    printf("Returned Value = %d\n", *(int*)res);

    return 0;


}

/*
                PROCESS

Address        Value
-------        -----

5000           result = 100

                 ▲
                 │
              return

                 │

                res

                 │
                 ▼

               5000

                 │
                 ▼

          *(int*)res

                 │
                 ▼

                100

*/