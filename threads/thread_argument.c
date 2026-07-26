#include<stdio.h>
#include<pthread.h>

void* printvalue(void* args){
    int *num = (int*)args;
    printf("Received Value = %d\n", *num);

    return NULL;
}

int main(){
    pthread_t t1;

    int value = 100;
    pthread_create(&t1,NULL,printvalue,&value);
    pthread_join(t1,NULL);

    return 0;
}
/*

Main Thread

+----------------------+
| value = 100          |
| Address = 0x1000     |
+----------------------+
          │
          │ &value
          ▼

Thread

arg = 0x1000
          │
          ▼

(int*)arg

          │
          ▼

num = 0x1000

          │
          ▼

*num = 100


*/