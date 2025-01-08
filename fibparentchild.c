#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int isPrime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) 
        if (n % i == 0) return 0;
    return 1;
}

int main() {
    int length = 10;
    int *arr = (int*malloc(sizeof(int)*length);

    if(arr == NULL) {
        printf("Memory not allocated.\n");
        return 1;
    }

    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork failed.\n");
        free(arr);
        return 1;
    }

    if(pid == 0) {
        arr[0] = 0;
        arr[1] = 1;
        for(int i = 2; i < length; i++) 
            arr[i] = arr[i-1] + arr[i-2];

        printf("child fib series:");
        for(int i=0; i<length; i++)
            printf("%d" ,arr[i]);
        printf("\n");
        exit(0);
    }
    else {
        printf("parent fib series:");
        for(int i=0; i<length; i++)
            printf("%d" ,arr[i]);
        printf("\n");
        
        printf("parent prme fibs");
        for(int i=0; i<length; i++)
            if(isPrime(arr[i]))
                printf("%d at %d pos", arr[i], i)
    }

    free(arr);
    return 0;
}