#include<stdio.h>
#include<unistd.h>

int main(){
    int x = 10;
        /*
    Initially:

    Parent Process (PID=100)

    STACK
    -----
    x = 10
    main()

    */

    int pid=fork();
       /*
    fork() creates child process.

    After fork():

    Parent Process            Child Process
    PID=100                   PID=101

    STACK                     STACK
    -----                     -----
    pid=101                   pid=0
    x=10                      x=10
    main()                    main()

    Both have separate copies of x
    */

    if(pid==0){
        x=20;
    }

        /*
    Only child executes this:

    Child STACK
    -----------
    x = 20

    Parent STACK remains:

    Parent STACK
    ------------
    x = 10

    Changing child variable
    does NOT affect parent.
    */

    printf("x = %d\n",x);
}