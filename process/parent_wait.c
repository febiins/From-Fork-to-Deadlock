#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    int status=1;

    int pid = fork();
    if(pid==0){
        printf("The child status code is: %d\n",status);
        printf("child process executed\n");
    }
    else{
        wait(&status);
        printf("The parent status code is: %d\n",status);
        printf("parent process executed\n");
    }
    return 0;
}
/*

Initially:

Parent Process

STACK
-----
status = 1


After fork():

Parent Process              Child Process

STACK                       STACK
-----                       -----
status = 1                  status = 1

Both processes get separate
copies of status.


Child executes:

"The child status code is 1"

(This is child's own local copy,
not OS status information)


Parent executes:

wait(&status)

Parent pauses until
child finishes.


Child finishes
↓
OS may overwrite parent's
status variable with child
termination information.
↓
Parent resumes execution.


Important:

Child status variable and
parent status variable are
different copies after fork().

*/