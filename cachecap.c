#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "timer.h"

#define KB 1024
#define MAXCAP 512 * KB
#define LINESIZE 64
#define STEPS 512 * 1024
#define RUNS 5

int main(){
        int arraysize, arraylength, lengthmod, run, i, j, sum = 0;
        long long start, end;
        float tv;
        int* array;
        float* timearray = malloc(RUNS * sizeof(float));

        for(i = 0; i < RUNS; i++){
            timearray[i] = 0.00;
        }

        for(arraysize = 1 * KB; arraysize < MAXCAP; arraysize *= 2){
            
            array = malloc(arraysize);
            arraylength = arraysize/sizeof(int);
            lengthmod = arraylength - 1;
            
            srand(time(NULL));
            for(i = 0; i < arraylength; i++){
                array[i] = rand()%5;
            }
            
            for(run = 0; run < RUNS; run++){
                start = wall_clock_time();

                for(i = 0; i < STEPS; i++){
                    array[(i*LINESIZE/sizeof(int)) & lengthmod]++;
                    //sum += array[(i*LINESIZE/sizeof(int)) & lengthmod];
                }
                end = wall_clock_time();
                timearray[run] =  ((float)(end-start))/1000000000;
            }
            

            /* sort array and get median */
            for(i = 0; i < RUNS-1; i++){
                for(j = 0; j < RUNS-i-1; j++){
                    if(timearray[j] > timearray[j+1]){
                        tv = timearray[j];
                        timearray[j] = timearray[j+1];
                        timearray[j+1] = tv;
                    }
                }
            }

            printf("arraylength (KB): %3d time:%lf\n", arraysize/KB, 
                   timearray[RUNS/2]);
            free(array);
            
     }
        
}
