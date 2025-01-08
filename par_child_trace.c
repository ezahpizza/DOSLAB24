#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){
    pid_t pid fork();
    if(pid < 0) {
        printf("fork faild");
        exit(1);
    }
    else if(pid == 0){
        printf("child %d\n",getpid());
    while(1){}
    else{
        printf("parent %d\n",getpid());
        wait(NULL); printf("parent process %d: child process finished\n", getpid());
    }
    return 0;
}