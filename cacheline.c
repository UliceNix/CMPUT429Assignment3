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
#include <sys/time.h>
#include <math.h>

#define KB 1024
#define MB 1024 * KB
#define CACHE_SIZE 128 * KB
#define ARRAY_SIZE 3 * MB
#define ARRAY_LENGTH ARRAY_SIZE/sizeof(int)
#define MAX_LINE_SIZE 512
#define RUNS 10

long long wall_clock_time();

void init_array(int *start){
        int i;       
        srand(time(NULL));
        for(i = 0; i < ARRAY_LENGTH; i++){
            start[i] = rand()%5;
        }
}

void init_time(float *start){
        int i;
        for(i = 0; i < ARRAY_LENGTH; i++){
            start[i] = 0.00;
        }
}

int main()
{
        int line_size, run, sum;

        /* used to record start time and end time*/
        long long start, end;
        float t1, t2, time_accu;
        
        /* Allocate an integer array and initialize it*/
        int* array = malloc(ARRAY_SIZE);
        int lengthmod = ARRAY_LENGTH - 1;

        /* Allocate a double array to record time */
        float* time_array = malloc(ARRAY_LENGTH*sizeof(double));

        FILE *fp;

        init_array(array);
        init_time(time_array);

        fp = fopen("cacheline.txt", "w+");
        if(!fp){
            perror("fopen error!\n"); exit(10);
        }

        for(line_size = 4; line_size < MAX_LINE_SIZE/sizeof(int); line_size*=2){
            time_accu = 0;
            for(run = 0; run < RUNS; run++){

                /* start timer*/
                start = wall_clock_time();
                int k =0;
                for(k; k < 512 * 1024;k++){
                    sum += array[(k*line_size) & lengthmod];
                    
                }
                end = wall_clock_time();
                time_array[run] = ((float)(end-start))/1000000000;
                if( fprintf(fp, "line_size: %d, Sum: %d, Time: %lf\n", line_size, sum, time_array[run]) < 0){
                    perror("fprint error\n"); exit(10);
                }
            }
            
            int c,d;
            for(c = 0; c < RUNS-1; c++){
                for(d = 0; d < RUNS-c-1; d++){
                    if(time_array[d] > time_array[d+1]){
                        float tv;
                        tv = time_array[d];
                        time_array[d] = time_array[d+1];
                        time_array[d+1] = tv;
                    }
                }
            }
            for(c = 0; c < RUNS; c++){
                printf("%lf \n", time_array[c]);
            }

            printf("size:%3lu Time:%lf\n", line_size*sizeof(int), time_array[RUNS/2]);
/*
            if( fprintf(fp, "line_size: %d, Sum: %d, Time: %lf\n", line_size, sum, time_accu) < 0){
                perror("fprint erroe\n"); exit(10);
            }
            */
            FILE* temp = fopen("/dev/null","w");
            fprintf(temp, "%d", sum);
        }

        if(fclose(fp)){
            perror("encountered fclose error"); exit(10);
        }
        
        free(array);
        free(time_array);
}


long long wall_clock_time() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (long long)(tv.tv_usec * 1000 + (long long)tv.tv_sec * 1000000000ll);
}


