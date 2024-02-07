/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: ipc.c
@version: I
Creation: 06/02/2024
Last modification: 06/02/2024
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#define SHM_SIZE 1024

int main(int argc, char** argv) {
    // two arguments checking
    if (argc != 3) {
        printf("Usage: %s <number> <letter>\n", argv[0]);
        return 1;
    }

    // number convertion from string to integer
    int n = atoi(argv[1]);

    // get the letter from the second argument (x)
    char x = argv[2][0];

    // variable for the shared memory
    int shmid;

    // attempt to create shared memory
    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("Error creating shared memory");
        return 1;
    }

    // child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("Error in fork");
        return 1;
    } else if (pid == 0) {

        // signal that the child process is ready
        printf("Child process ready\n");

        // attach the shared memory segment to the child process address space
        char* shmem = shmat(shmid, NULL, 0);
        if (shmem == (void*) -1) {
            perror("Error attaching shared memory to child process");
            return 1;
        }

        sleep(1);

        // write to shared memory
        for (int i = 0; i < SHM_SIZE; i++) {
            shmem[i] = x;
        }

        // detach the shared memory from the child process address space
        if (shmdt(shmem) == -1) {
            perror("Error detaching shared memory from child process");
            return 1;
        }

        return 0;
    } else {
        // parent process
        // attach the shared memory segment to the parent process address space
        char* shmem = shmat(shmid, NULL, 0);
        if (shmem == (void*) -1) {
            perror("Error attaching shared memory to parent process");
            return 1;
        }

        for (int i = 0; i < SHM_SIZE; i++) {
            // check if the iteration number is divisible by n
            if ((i + 1) % n == 0) {
                printf("Sending '%c' to child process\n", x);
                shmem[i] = x;
            }
        }

        // waiting for the child process to finish
        wait(NULL);

        // display the content of shared memory
        printf("Contents of shared memory:\n");
        for (int i = 0; i < SHM_SIZE; i++) {
            printf("%c", shmem[i]);
        }
        printf("\n");

        // detach the shared memory from the parent process address space
        if (shmdt(shmem) == -1) {
            perror("Error detaching shared memory from parent process");
            return 1;
        }

        // delete the shared memory
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("Error deleting shared memory");
            return 1;
        }

        return 0;
    }
}