#include<stdio.h>
#include<unistd.h>

int main() {

    fork();

    fork();

    printf("Hi\n");

    return 0;
}