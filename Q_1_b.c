#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int factorial(int n){
    if(n == 0 || n == 1){
        return n;
    }
    return n*factorial(n-1);
}

int fibonacci(int n){
    printf("0 ");
    if(n == 1){
        printf("\n");
        return 0;
    }
    printf("1 ");
    if(n == 2){
        printf("\n");
        return 0;
    }
    int a = 1;
    int b = 1;
    int c = 1;
    for(int i = 1; i<n; i++){
        printf("%d ", c);
        c = a+b;
        a = b;
        b = c;
    }
    printf("\n");
    return 0;
}

int main(int argc, char *argv[]){

    int rc = fork();

    if (rc < 0){
        printf("fork failed\n");
        exit(1);
    }

    else if(rc == 0){
        printf("Child ID %d\n", (int) getpid());
        printf("Factorial of 4 is %d\n", factorial(4));
    }

    else{
        int wc = wait(NULL);
        printf("Parent (P) is having ID %d\n", (int) getpid());
        printf("Fibonacci series upto 16 terms is: \n");
        fibonacci(16);
    }

    return 0;
}