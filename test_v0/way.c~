#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define KB 1024
#define MB 1024 * KB
#define REPS 2 * 1024 * 1024

/* */

int main(int argc, char* argv[]){
        
        int arraysize = 5 * MB, 
                arraylength = arraysize/sizeof(int), 
                lengthmod = arraylength - 1,
                i, j, k, cap;
        long long start, end;
        int* array;

        if(argc > 1){
            cap = atoi(argv[1]);
        }else{
            printf("Please input the cache capacity in KB.\n");
            return 1;
        }
 
        /* array list initialization*/
        array = malloc(arraysize);
        srand(time(NULL));
        for(i = 0; i < arraylength; i++)
                array[i] = rand()%5;
        
        /* get a random start point*/
        k = rand()%lengthmod;

        /*
         * We find the correct way order by trying from i = 1 to 64 
         * Assume the number of sets in the cache is n, so every
         * (CAPS/n)th byte will compete for the same cache line.
         * We access k + (j*CAPS/n)th byte in each iteration.
         * When CAPS/i >= CAPS/n, namely i <= n, the execution time
         * will be relatively high since each access will cause cache
         * miss. We'll see a decrease in execution time when i > n.
         */
        for(i = 1; i < 128; i *= 2){
            start = wall_clock_time();
            for(j = 1; j < REPS; j++){
                array[k&lengthmod]++;
                k+=cap/i/sizeof(int);
            }
            end = wall_clock_time();
            printf("test way: %2d time:%lf\n", i, 
                   ((float)(end-start))/1000000000);
            
        }
        
        free(array);
        return 0;
}

/**
OUTPUT FOR MACHINE 1 (4 way)
test way:  1 time:0.009787
test way:  2 time:0.010136
test way:  4 time:0.010136 (n = 4)
test way:  8 time:0.008127 (****)
test way: 16 time:0.008127
test way: 32 time:0.008126
test way: 64 time:0.008126

OUTPUT FOR MACHINE 2 (2 way)
test way:  1 time:0.023413
test way:  2 time:0.024416
test way:  4 time:0.020132 (****)
test way:  8 time:0.019937
test way: 16 time:0.019845
test way: 32 time:0.019916
test way: 64 time:0.019952


OUTPUT FOR MACHINE 3 (direct mapped)
test way:  1 time:0.020136
test way:  2 time:0.013693 (****)
test way:  4 time:0.013632
test way:  8 time:0.013631
test way: 16 time:0.013631
test way: 32 time:0.013631
test way: 64 time:0.013631

 */
