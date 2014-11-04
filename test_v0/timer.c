#include "timer.h"


long long wall_clock_time() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (long long)(tv.tv_usec * 1000 + (long long)tv.tv_sec * 1000000000ll);
}
