#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define KB 1024
#define MB KB * 1024
#define ARRAY_SIZE 3 * MB
#define ARRAY_LENGTH ARRAY_SIZE/sizeof(int)
#define STEPS  MB
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
                array[k & lengthmod]++;
                k += stepsize * i;
            }
            
            /* end timer */
            end = wall_clock_time();
            float totaltime = (end-start);

            start = wall_clock_time();
            for(i = 0; i < STEPS; i++){
                i = (i*stepsize);
            }
            end = wall_clock_time();
            float overhead = (end - start);

            /* convert number of words back to bytes for convenience*/
            printf("stepsize: %3lu time%lf\n", stepsize*sizeof(int), 
                   (float)(totaltime-overhead));           
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
