#include<stdio.h>
#include<unistd.h>

int main(){
    int pid = fork();

    if(pid==0){
        printf("child process id : %d\n",getpid());
        printf("parent process id : %d\n",getppid());

    }else{
        printf("parent id is :%d\n",getpid());
    }
}