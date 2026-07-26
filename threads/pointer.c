#include<stdio.h>

int main(){
    int value=10;
    int *p=&value;

    printf("%p",(void*)p);
    printf("\n%d",*p);
}