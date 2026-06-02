#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {

    int status = 100;

    int pid = fork();

    if(pid == 0){

        return 0;

    }

    else{

        printf("Before wait: %d\n", status);

        wait(&status);

        printf("After wait: %d\n", status);

    }

}