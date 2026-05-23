#include<stdio.h>
#include<unistd.h>

int main(){

    /*
    Program starts:

    Parent Process
    PID = 100 (example)

    STACK
    -----
    main()

    */
    int pid = fork();

       /*
    After fork():

             Parent Process
                 PID=100
                    |
                    |
             Child Process
                 PID=101


    Parent STACK                Child STACK
    ------------                -----------
    pid = 101                   pid = 0
    main()                      main()

    Parent gets:
        pid = child PID

    Child gets:
        pid = 0
    */

    if(pid==0){

        /*
        Child executes:

        getpid()
            ↓
        returns 101

        getppid()
            ↓
        returns 100
        */
        printf("child process id : %d\n",getpid());
        printf("parent process id : %d\n",getppid());

    }else{
          /*
        Parent executes:

        getpid()
            ↓
        returns 100
        */
        printf("parent id is :%d\n",getpid());
    }
}