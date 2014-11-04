#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define KB 1024
#define MB KB * 1024
#define ARRAY_SIZE 3 * MB
#define ARRAY_LENGTH ARRAY_SIZE/sizeof(int)
#define STEPS 512 * KB
#define MAXLINESIZE 1024

/* init_array function initializes an integer array with integers from 0 to 4.*/
void init_array(int *start);

int main(){

        /* initialize variables*/
        long long start, end; 
        int stepsize, i, j, k, run, sum, lengthmod = ARRAY_LENGTH-1;
        int* array = malloc(ARRAY_SIZE);
        init_array(array);

        printf("start testing!\n");

        /* 
         * stepsize is measured by a word (4bytes). we iterate the array by 
         * a word, not by a byte. Have to be careful with word and byte
         */
        for(stepsize = 1; stepsize < MAXLINESIZE/sizeof(int); stepsize *= 2){

            /* start timer */
            start = wall_clock_time();
            for(i = 0; i < STEPS; i++){

                /* 
                 * modify the array every (i*stepsize)%lengthmod integer
                 * the expression in [] is same as (i*stepsize)%lengthmod 
                 */
                array[(i * stepsize) & lengthmod]++;
            }
            
            /* end timer */
            end = wall_clock_time();

            /* convert number of words back to bytes for convenience*/
            printf("stepsize: %3lu time%lf\n", stepsize*sizeof(int), 
                   ((float)(end-start))/1000000000);           
        }
        
        /* free allocated memory*/
        free(array);
}

/* initialize an array*/
void init_array(int *start){
        int i;       

        srand(time(NULL));
        for(i = 0; i < ARRAY_LENGTH; i++){
            start[i] = rand()%5;
        }
}

/**
----OUTPUT FOR MACHINE 1: (cache line size = 64 bytes)
stepsize:   4 time0.001704
stepsize:   8 time0.002097
stepsize:  16 time0.001170
stepsize:  32 time0.001049
stepsize:  64 time0.002032 (***)
stepsize: 128 time0.002031
stepsize: 256 time0.002032
stepsize: 512 time0.002031

----OUTPUT FOR MACHINE 2: (cache line size = 128 bytes)
stepsize:   4 time0.001508
stepsize:   8 time0.001704
stepsize:  16 time0.001287
stepsize:  32 time0.001114
stepsize:  64 time0.001245
stepsize: 128 time0.002032 (***)
stepsize: 256 time0.002031
stepsize: 512 time0.002032

----OUTPUT FOR MACHINE 3: (cache line size = 8bytes)
stepsize:   4 time0.004457
stepsize:   8 time0.007601 (***)
stepsize:  16 time0.003015
stepsize:  32 time0.002097
stepsize:  64 time0.002098
stepsize: 128 time0.002097
stepsize: 256 time0.002097
stepsize: 512 time0.002097
*/
