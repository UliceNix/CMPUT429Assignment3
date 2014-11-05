#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define KB 1024
#define MB 1024 * KB
#define REPS 2 * 1024 * 1024

int main(int argc, char* argv[]){
        
        int arraysize = 5 * MB, 
                arraylength = arraysize/sizeof(int), 
                lengthmod = arraylength - 1,
                i, j, k, cap;
        long long start, end;
        volatile int* array = malloc(arraysize);

        if(argc > 1){
            cap = atoi(argv[1])*KB;
            printf("Cache capacity: %d\n", cap);
        }else{
            printf("Please input cache capacity in KB.\n");
            return 1;
        }
 
        /* array list initialization*/
        srand(time(NULL));
        for(i = 0; i < arraylength; i++)
                array[i] = rand()%5;
        
        /* get a random start point*/
        k = rand()%lengthmod;

        /*
         * We find the correct way order by trying from i = 1 to 64 
         * Assume the number of sets in the cache is n, so every
         * (CAPS/n)th byte will compete for the same cache line.
         * We access k + (j*CAP/n)th byte in each iteration.
         * When CAPS/i >= CAP/n, namely i <= n, the execution time
         * will be relatively high since each access will cause cache
         * miss. We'll see a decrease in execution time when i > n.
         */
        printf("testing starts!\n");
        for(i = 1; i < 64; i *= 2){

            int inc = cap/i/sizeof(int);

            start = wall_clock_time();
            for(j = 0; j < REPS; j++){
                array[k&lengthmod]++;
                k+=inc;
            }
            end = wall_clock_time();
            float total = end - start;

            start = wall_clock_time();
            for(j = 0; j < REPS; j++){
                k+=inc;
            }
            end = wall_clock_time();
            float overhead = end - start;
            printf("test way: %2d time:%lf\n", i, 
                   ((float)(total - overhead))/1000000);
            
        }
        
        free((void*)array);
}
