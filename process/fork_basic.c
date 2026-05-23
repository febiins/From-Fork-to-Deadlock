#include<stdio.h>
#include<unistd.h>

int main(){
    /*
    fork() creates a new process.

    Before fork():

        P1 (only one process)

    After fork():

        Parent Process (P1)
               |
        Child Process  (P2)

    Both processes continue execution
    from the next instruction after fork().
    */
    
    fork();
     /*
    Since both parent and child execute
    this line, "Hi" prints twice.

    Parent -> Hi
    Child  -> Hi
    */
    printf("Hi\n");

     /*
    return 0 means successful termination
    of the process.

    Parent ends.
    Child ends.
    */
    

    return 0;
}

//fork() creates a new child process, which is initially a copy of the parent process and continues execution independently.