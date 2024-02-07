/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: 
@version: I
Creation: 06/02/2024
Last modification: 06/02/2024
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    clock_t start, end;
    double elapsed_time;

    start = clock();

    for (int i = 0; i < 1000000; ++i) {
        printf("Iteration %d\n", i);
    }
    for (int i = 0; i < 1000000; ++i) {
        printf("Iteration %d\n", i);
    }
    for (int i = 0; i < 1000000; ++i) {
        printf("Iteration %d\n", i);
    }

    // last loop time
    end = clock();

    // elapsed time calculation
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}