#include<stdio.h>
#include<stdlib.h>

int main() {

    int *p = malloc(sizeof(int));

    *p = 50;

    printf("Before free: %d\n", *p);

    free(p);

    printf("After free: %d\n", *p);   // dangling pointer:- Pointer exists, memory removed

    //To solve it use

    p = NULL;

    printf("After NULL: %d\n", p);

    return 0;
}

// int p
// *p=malloc(sizeof(int))