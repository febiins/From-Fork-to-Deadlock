#include<stdio.h>
#include<stdlib.h>

int main() {

    int *p1;
    int *p2;

    p1 = malloc(5 * sizeof(int));
    p2 = calloc(5, sizeof(int));

    printf("malloc:\n");

    for(int i=0;i<5;i++)
        printf("%d ", p1[i]);

    printf("\n\ncalloc:\n");

    for(int i=0;i<5;i++)
        printf("%d ", p2[i]);

    free(p1);
    free(p2);

    return 0;
}

// malloc:- Allocates memory but does NOT initialize values

//calloc:- Allocates AND initializes to zero. Allocates one contiguous block of memory and initializes all bytes to zero