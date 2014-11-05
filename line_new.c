#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define KB 1024
#define MB KB * 1024
#define ARRAY_SIZE 8 * MB
#define ARRAY_LENGTH ARRAY_SIZE/sizeof(int)
#define STEPS  4 * MB
#define MAXLINESIZE 1024

/* init_array function initializes an integer array with integers from 0 to 4.*/
void init_array(int *start);

int main(){

        /* initialize variables*/
        long long start, end; 
        int stepsize, i, j, k = 0, run, lengthmod = ARRAY_LENGTH-1;
        int* array = malloc(ARRAY_SIZE);
        init_array(array);

        printf("start testing!\n");
       

        /**
         * This is a new method of measuring cache line size.
         * In this method, we iterate through the array only once in each trial
         * but with different stepsize.
         * So before the stepsize exceeds the cache line size, we will access every
         * cache line in the cache, so assume the number of total cache line access 
         * is n. After the stepsize exceeds the cache line size, the number of cache
         * line access will decrease, so will the execution time. (the first stepsize
         * that is greater than the real cache line size will lead the number of cache
         * access to n/2, and the second one will make it n/4, ....)
         */
        for(stepsize = 1; stepsize < MAXLINESIZE/sizeof(int); stepsize *= 2){
            start = wall_clock_time();
            for(i = 0; i < ARRAY_LENGTH; i += stepsize){
                array[i&lengthmod]++;
            }
            end = wall_clock_time();
            /* time is measured in microseconds*/
            printf("stepsize: %3lu  time:%lf\n", stepsize*sizeof(int),
                   ((float) (end-start)/1000000));
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
