#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define KB 1024
#define MB KB * 1024
#define ARRAY_SIZE 64 * MB
#define ARRAY_LENGTH ARRAY_SIZE/sizeof(int)
#define MAXLINESIZE 1024

/* init_array function initializes an integer array with integers from 0 to 4.*/
void init_array(int *start);

int main(){

        /* initialize variables*/
        long long start, end; 
        int stepsize, i;
        int* array = calloc(ARRAY_LENGTH, sizeof(int));

        printf("start testing!\n");
       

        /**
         * This is a new method of measuring cache line size.
         * In this method, we iterate through the array only once in each trial
         * but with different stepsize.
         * Assume the number of cache line access is n for the first iteration, 
         * then when we are in the xth iteration, the number of cache line access 
         * will be n/(2^x), but the execution time will not decrease in this fashion.
         * When 2^x < cache line size, we will access every cache line in the cache
         * and even access one cache line multiple times. So we can expect to see 
         * turbulences of execution time. When 2^x == cache line size, we will know
         * the time of accessing each cache line T. So in the next iteration, 2^(x+1),
         * we will access every other cache line instead of every cache line, and we
         * can expect to the execution time to be T/2. So by this time, we'll know
         * the cache line size.
         */
        for(stepsize = 1; stepsize < MAXLINESIZE/sizeof(int); stepsize *= 2){
            start = wall_clock_time();
            for(i = 0; i < ARRAY_LENGTH; i += stepsize){
                array[i]++;
            }
            end = wall_clock_time();
            /* time is measured in microseconds*/
            printf("stepsize: %3lu  time:%lf\n", stepsize*sizeof(int),
                   ((float) (end-start)/1000000));
        }
        /* free allocated memory*/
        free(array);
}

/**
Machine 1:
stepsize:   4  time:81.786003
stepsize:   8  time:60.813999
stepsize:  16  time:21.520000
stepsize:  32  time:14.679000
stepsize:  64  time:14.586000 (T)
stepsize: 128  time:7.293000  (T/2)
stepsize: 256  time:3.646000
stepsize: 512  time:1.823000

Machine 2:
stepsize:   4  time:66.057999
stepsize:   8  time:45.088001
stepsize:  16  time:25.341999
stepsize:  32  time:14.156000
stepsize:  64  time:13.893000
stepsize: 128  time:13.893000(T)
stepsize: 256  time:6.947000 (T/2)
stepsize: 512  time:3.474000

Machine 3:


*/
