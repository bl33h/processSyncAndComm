/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: fourIterationsFork.c
@version: I
Creation: 05/02/2024
Last modification: 05/02/2024
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 4; ++i) {
        pid_t child = fork();

        if (child == 0) {
            // child process
            printf("I am child %d, my PID is %d\n", i + 1, getpid());
            break;
            // loop exit
        } else if (child == -1) {
            fprintf(stderr, "Error creating child process in iteration %d\n", i + 1);
            return 1;
        } else {
            // parent process
            printf("Process %d has started\n", i + 1);
        }
    }

    // wwaiting till children finish
    for (int i = 0; i < 4; ++i) {
        wait(NULL);
    }

    printf("Parent process exiting\n");

    return 0;
}