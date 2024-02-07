/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: parent.c
@version: I
Creation: 06/02/2024
Last modification: 06/02/2024
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Error in fork");
        return 1;
    } else if (pid == 0) {
        // child process
        for (int i = 1; i <= 4000000; ++i) {
            printf("%d\n", i);
        }
    } else {
        // parent process
        while (1) {
        }
    }

    return 0;
}