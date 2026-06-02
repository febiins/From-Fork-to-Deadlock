#include<stdio.h>
#include<unistd.h>

int main(){
    int pid = fork();

    if (pid==0){
        sleep(5);

        printf("Child Process\n");
        printf("Parent PID = %d\n", getppid());
    }
    else{
        printf("Parent Process\n");
        printf("Parent PID = %d\n", getpid());

        return 0;
    }
}

 /*
    =====================================================
                    ORPHAN PROCESS DEMO
    =====================================================

    Step 1: Program starts

            Parent Process
                PID=100

            STACK
            -----
            main()


    Step 2: fork() creates child

                Parent (PID=100)
                       |
                       |
                Child  (PID=101)


    Step 3: Parent executes first

                Parent Process
                Parent PID = 100

                return 0;
                     ↓
                Parent Terminates


    Step 4: Child is sleeping

                Parent ❌ Dead

                Child (PID=101)
                sleep(5)

                Child has no parent now.

                This child becomes
                an ORPHAN PROCESS.


    Step 5: OS adopts the child

                init/systemd (PID=1)
                        |
                        |
                   Child(PID=101)

                New Parent Assigned


    Step 6: Child wakes up

                printf("Child Process");

                getppid()
                    ↓

                returns PID of
                init/systemd
                (usually 1 or another
                 system process PID)


    =====================================================
    Definition:

    Orphan Process:
    A child process whose parent
    has terminated before the child.

    OS automatically assigns a
    new parent (init/systemd).

    =====================================================
    */