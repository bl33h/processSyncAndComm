/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: time1.c
@version: I
Creation: 06/02/2024
Last modification: 06/02/2024
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // error while forking
        perror("Error while forking");
        return 1;
    } else if (pid == 0) {
        // Ccild process
        printf("This is the child process.\n");
    } else {
        // parent process
        while(1) {

        }
    }

    return 0;
}