#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

#define KB 1024
#define MAXCAP KB * KB
#define STEPS 2 * 1024 * 1024

int main(int argc, char* argv[]){

        int arraysize, arraylength, lengthmod, i, linesize;
        long long start, end;
        int* array;

        if(argc > 1){
            linesize = atoi(argv[1]);
        }else{
            printf("Please input the linesize in bytes.\n");
            return 1;
        }


        for(arraysize = 2 * KB; arraysize < MAXCAP; arraysize *= 2){
            
            /* allocate memory and initialize the array */
            array = malloc(arraysize);
            arraylength = arraysize/sizeof(int);
            lengthmod = arraylength - 1;
            
            srand(time(NULL));
            for(i = 0; i < arraylength; i++){
                array[i] = rand()%5;
            }
            
            /* start the timer, modify each cache line */
            start = wall_clock_time();
            for(i = 0; i < STEPS; i++){
                array[(i*linesize/sizeof(int)) & lengthmod]++;
            }
            end = wall_clock_time();
            
            /* print the output */
            printf("test cache capacity (KB): %3d time:%lf\n", arraysize/KB, 
                  ((float)(end-start))/1000000000);
                
            free(array);
            
        }
        return 0;
        
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

