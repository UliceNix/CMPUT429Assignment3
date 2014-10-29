/*
 * cache line test range: 4 byte - 256 byte
 * But we need an array that could not fit in the cache so that after iterating
 * an array once previous fetched cache lines will be flushed out and will not
 * the next iteration.
 * The largest cache possible is 128KB. So we'll set our data array to be larger
 * than 128KB.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define KB 1024
#define CACHE_SIZE 128 * KB
#define ARRAY_SIZE 130 * KB
#define ARRAY_LENGTH ARRAY_SIZE/sizeof(int)
#define MAX_LINE_SIZE 512
#define RUNS 4


void init_array(int *start){
        int i;       
        srand(time(NULL));
        for(i = 0; i < ARRAY_LENGTH; i++){
            start[i] = rand()%5;
        }
}

void init_time(double *start){
        int i;
        for(i = 0; i < ARRAY_LENGTH; i++){
            start[i] = 0.00;
        }
}

int main()
{
        int line_size, run, sum;

        /* used to record start time and end time*/
        struct timeval start, end;
        double t1, t2, time_accu;
        
        /* Allocate an integer array and initialize it*/
        int* array = malloc(ARRAY_SIZE);
        int lengthmod = ARRAY_LENGTH - 1;

        /* Allocate a double array to record time */
        double* time_array = malloc(ARRAY_LENGTH*sizeof(double));

        FILE *fp;

        init_array(array);
        init_time(time_array);

        fp = fopen("cacheline.txt", "w+");
        if(!fp){
            perror("fopen error!\n"); exit(10);
        }

        for(line_size = 4; line_size < MAX_LINE_SIZE; line_size*=2){
            time_accu = 0;
            for(run = 0; run < RUNS; run++){

                /* start timer*/
                gettimeofday(&start, NULL);
                t1 = start.tv_usec + start.tv_sec * 1000000;

                int k =0;
                for(k; k < 512 * 1024;k++){
                    //printf("line_size:%d, k:%d, /k*i&lengthmod:%d\n",line_size, k, (k*line_size)&lengthmod);
                    // should do a sum to prevent compiler from optimizing
                    sum += array[(k*line_size)&lengthmod];
                    
                }
                gettimeofday(&end, NULL);
                t2 = end.tv_usec + end.tv_sec * 1000000;

                /* record the time of run */
                time_accu += t2 - t1;
            }
            time_accu = time_accu/RUNS;
            if( fprintf(fp, "line_size: %d, Sum: %d, Time: %lf\n", line_size, sum, time_accu) < 0){
                perror("fprint erroe\n"); exit(10);
            }
            
        }

        if(fclose(fp)){
            perror("encountered fclose error"); exit(10);
        }

}
