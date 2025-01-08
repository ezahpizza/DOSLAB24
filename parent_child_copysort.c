#include<stdio.h>
#include<unistd.h>
int main() {
    if(fork()>0)
    sleep(1);
    else {
        printf("Child 1 id %d and parent id %d\n", getpid(), getppid()); 
        printf("\n\n Copying f1.txt to f2.txt......\n\n"); 
        execlp("cp","cp","-f", "f1.txt", "f2.txt", NULL);
    }
    if(fork()>0)
    sleep(1);
    else {
        printf("Child 2 id %d and parent id =%d\n",getpid(), getppid()); 
        printf("\n\n Content of f2.txt is......\n\n"); 
        execlp("cat", "cat", "f2.txt", NULL);
    }
    if(fork()>0)
    sleep(1);
    else {
        printf("Child 3 id %d and parent id %d\n", getpid(), getppid());
        printf("\n\n Content of f2.txt in reverse sorted orderd is......\n\n"); 
        execlp("sort", "sort","-r", "f2.txt", NULL);
    }
    printf("I am the parent with id %d\n", getppid()); 
    return 0;
}