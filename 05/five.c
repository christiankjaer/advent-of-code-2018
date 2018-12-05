#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define INPUT 50000

char input[INPUT];

int ex1(char c) {

    char b[INPUT];

    int elems = 0;
    // filter
    for (int i = 0; i < INPUT; i++) {
        if (input[i] == c || input[i] == c-32) continue;
        b[elems++] = input[i];
    }

    // Switch these buffers at each iteration.
    int changed;

    do {
        changed = 0;
        int i = 0;
        int j = 0;
        while (i < elems-1) {
            char c1 = b[i++];
            char c2 = b[i];
            if (c1 + 32 == c2 || c1 == c2 + 32) {
                i++;
                changed = 1;
                continue;
            }
            b[j++] = c1;
        }
        // Handling the end.
        if (i == elems-1) {
            b[j++] = b[i++];
        }
        elems = j;

    } while(changed);

    return elems;
}

int main() {

    FILE *fp = fopen("input", "r");
    fread(input, sizeof(char), INPUT, fp);

    struct timeval begin;
    gettimeofday(&begin, NULL);

    int e1 = ex1('\0');
    printf("ex1: %d\n", e1);

    int e2 = e1;

    #pragma omp parallel for reduction(min:e2)
    for (char c = 'a'; c <= 'z'; c++) {
        int val = ex1(c);
        if (val < e2) e2 = val;
    }
    printf("ex2: %d\n", e2); 

    struct timeval end;
    gettimeofday(&end, NULL);
    int begint =  begin.tv_sec * (int)1e6 + begin.tv_usec;
    int endt =  end.tv_sec * (int)1e6 + end.tv_usec;

    printf("took %d us\n", endt - begint);

    return 0;

}
