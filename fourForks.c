/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: fourForks.c
@version: I
Creation: 05/02/2024
Last modification: 05/02/2024
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int process_number = 1;

    // first fork
    pid_t child1 = fork();

    if (child1 == 0) {
        printf("I am child %d, my PID is %d\n", process_number, getpid());

    // parent
    } else {
        process_number++;
        pid_t child2 = fork();

        if (child2 == 0) {
            printf("I am child %d, my PID is %d\n", process_number, getpid());

        } else {
            process_number++;
            pid_t child3 = fork();

            if (child3 == 0) {
                printf("I am child %d, my PID is %d\n", process_number, getpid());

            } else {
                process_number++;
                pid_t child4 = fork();

                if (child4 == 0) {
                    printf("I am child %d, my PID is %d\n", process_number, getpid());
                } else {
                    process_number++;

                    // waiting till children finish 
                    for (int i = 0; i < 4; ++i) {
                        wait(NULL);
                    }

                    printf("Parent process exiting\n");
                }
            }
        }
    }

    return 0;
}