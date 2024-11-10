// 1. The precision of gettimeofday() is down to milliseconds. To time such an experiment correctly
// we need to run enough iterations for at least a few milliseconds.

// 5. To ensure that our loop runs, we can put buffer/useless operations inside each loop to
// ensure that the loop is not amortized or removed. 

// 6. If the execution switches CPU's, the TLB won't carry over, causing the experiment to report incorrect
// results. We can use an in-built function to fix the execution to one CPU.

// 7. If the array isn't initialized, yes the cost of initialization may be more expensive.
// 
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int pagesize = 4096;
    int pages = atoi(argv[1]);
    int trials = 10000;
    int *total_pages = malloc(pagesize * pages);
    int jump = pagesize / sizeof(int);

    struct timeval start, end;

    gettimeofday(&start, NULL);

    for (int i = 0; i < trials; i++){
        for (int j = jump; j < jump * pages; j += jump){
            total_pages[j] += 1;
        }
    }

    gettimeofday(&end, NULL);

    // Calculate time
    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    long elapsed = seconds * 1000000 + microseconds;

    printf("Time taken for %d pages and %d trials: %ld microseconds\n", pages, trials, elapsed);

    free(total_pages);
    return 0;
}