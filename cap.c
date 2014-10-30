#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

#define KB 1024
#define MAXCAP 512 * KB
#define LINESIZE 64
#define STEPS 512 * 1024

int main(){
        int arraysize, arraylength, lengthmod, run, i, j, sum = 0;
        long long start, end;
        float tv;
        int* array;


        for(arraysize = 1 * KB; arraysize < MAXCAP; arraysize *= 2){
            
            array = malloc(arraysize);
            arraylength = arraysize/sizeof(int);
            lengthmod = arraylength - 1;
            
            srand(time(NULL));
            for(i = 0; i < arraylength; i++){
                array[i] = rand()%5;
            }
            start = wall_clock_time();

            for(i = 0; i < STEPS; i++){
                array[(i*LINESIZE/sizeof(int)) & lengthmod]++;
            }
            end = wall_clock_time();
            printf("test cache capacity (KB): %3d time:%lf\n", arraysize/KB, 
                  ((float)(end-start))/1000000000);

            free(array);
            
     }
        
}

