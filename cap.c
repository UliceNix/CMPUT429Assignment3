#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

#define KB 1024
#define MAXCAP 512 * KB

/* This should be manually changed to match the cache 
 * configuration of the simulator
 * /
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
/**
----OUTPUT FOR MACHINE 1 (cache cap = 64 KB line size = 64 bytes)
test cache capacity (KB):   1 time:0.001311
test cache capacity (KB):   2 time:0.001311
test cache capacity (KB):   4 time:0.001311
test cache capacity (KB):   8 time:0.001310
test cache capacity (KB):  16 time:0.001311
test cache capacity (KB):  32 time:0.001311
test cache capacity (KB):  64 time:0.001315
test cache capacity (KB): 128 time:0.002097 (***)
test cache capacity (KB): 256 time:0.002097

----OUTPUT FOR MACHINE 2 (cache cap = 32 KB line size = 128 bytes)
test cache capacity (KB):   1 time:0.000786
test cache capacity (KB):   2 time:0.000786
test cache capacity (KB):   4 time:0.000786
test cache capacity (KB):   8 time:0.000786
test cache capacity (KB):  16 time:0.000786
test cache capacity (KB):  32 time:0.000787
test cache capacity (KB):  64 time:0.002050 (***)
test cache capacity (KB): 128 time:0.002050
test cache capacity (KB): 256 time:0.002050

----OUTPUT FOR MACHINE 3(cache cap = 16 KB line size = 8 bytes)
test cache capacity (KB):   1 time:0.002098
test cache capacity (KB):   2 time:0.002097
test cache capacity (KB):   4 time:0.002098
test cache capacity (KB):   8 time:0.002097
test cache capacity (KB):  16 time:0.002097 
test cache capacity (KB):  32 time:0.007602 (***)
test cache capacity (KB):  64 time:0.007601
test cache capacity (KB): 128 time:0.007601
test cache capacity (KB): 256 time:0.007601
 */

