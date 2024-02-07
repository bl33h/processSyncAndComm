/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: time1.c
@version: I
Creation: 06/02/2024
Last modification: 06/02/2024
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid, grandchild_pid, great_grandchild_pid;
    clock_t start, end, child_clock, grandchild_clock;

    // starting time
    start = clock();

    // first child process
    child_pid = fork();

    if (child_pid == 0) {

        // time just before the grandchild fork
        child_clock = clock();
        grandchild_pid = fork();

        if (grandchild_pid == 0) {
            
            grandchild_clock = clock();

            great_grandchild_pid = fork();

            if (great_grandchild_pid == 0) {

                for (int i = 0; i < 1000000; ++i) {
                    printf("Iteration %d\n", i);
                }
            } else {

                // waiting for the great-grandchild process to finish
                wait(NULL);
            }
        } else {
            wait(NULL);
        }
    } else {
        
        wait(NULL);

        // ending time
        end = clock();

        // elapsed time for the child process
        double child_elapsed_time = (double)(end - child_clock) / CLOCKS_PER_SEC;
        printf("Child process elapsed time: %f seconds\n", child_elapsed_time);

        // elapsed time for the grandchild process
        double grandchild_elapsed_time = (double)(end - grandchild_clock) / CLOCKS_PER_SEC;
        printf("Grandchild process elapsed time: %f seconds\n", grandchild_elapsed_time);

        // overall elapsed time
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Overall elapsed time: %f seconds\n", elapsed_time);
    }

    return 0;
}