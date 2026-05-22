#include<stdio.h>
#include<unistd.h>

int main(){
    int pid=fork();

    if(pid==0){
        printf("child process is activated\n");
    }else{
        printf("parent process is activated\n");
    }

    return 0;
}
/*
step 1:

Process: P1

STACK
-----
main()

execute -> int pid = fork();

fork creates the child process

Now:

Parent Process (P1)           Child Process (P2)

STACK                         STACK
-----                         -----
pid = childPID                pid = 0
main()                        main()

parent stack:

STACK
-----
pid = 105
main()

child stack:

STACK
-----
pid = 0
main()


Total execution:

fork()

     ┌────────────── Parent ──────────────┐
                                        
STACK                                   STACK
-----                                   -----
pid=105                                 pid=0
main()                                  main()

if(pid==0) → False                      if(pid==0) → True
↓                                       ↓

Print Parent                            Print Child


*/