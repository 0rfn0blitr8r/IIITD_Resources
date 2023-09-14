#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    int parentID = (int) getpid();
    printf("Parent (P) is having ID %d\n", parentID);

    int rc = fork();

    if (rc < 0){
        printf("fork failed\n");
        exit(1);
    }

    else if(rc == 0){
        printf("Child is having ID %d\n", (int) getpid());
        printf("My Parent ID is %d\n", parentID);
    }

    else{
        // printf("Parent (P) is having ID %d\n", parentID);
        int wc = wait(NULL);
        printf("ID of P's Child is %d\n", rc);
    }

    return 0;
}