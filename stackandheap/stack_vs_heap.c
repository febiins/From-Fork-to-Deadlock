#include<stdio.h>
#include<stdlib.h>

void demo(){
    int x=5; //stack

    int *p= malloc(sizeof(int)); //heap
    *p=20;

    printf("stack variable x = %d\n",x);
    printf("heap value *p = %d\n",*p);

    printf("Address of x: %p\n",&x); 
    printf("Address stored in p: %p\n",p); //heap address

    free(p);


}

int main(){
    demo();
    return 0;
}

/*

main()
 ↓
demo()
 ↓
x created (stack)
 ↓
p created (stack)
 ↓
malloc() → heap allocated
 ↓
*p = 20
 ↓
print values
 ↓
free(p)
 ↓
demo() ends → stack removed
 ↓
main() ends
 ↓
program exits

*/