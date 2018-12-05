#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>

#define INPUT 50000

char input[INPUT];
char b1[INPUT];
char b2[INPUT];

int ex1(char c) {

    int elems = 0;
    // filter
    for (int i = 0; i < INPUT; i++) {
        if (input[i] == c || input[i] == c-32) continue;
        b1[elems++] = input[i];
    }

    // Switch these buffers at each iteration.
    char* from = b1;
    char* to = b2;

    int changed;

    do {
        changed = 0;
        int i = 0;
        int j = 0;
        while (i < elems-1) {
            char c1 = from[i];
            char c2 = from[i+1];
            if (c1 + 32 == c2 || c1 == c2 + 32) {
                i += 2;
                changed = 1;
                continue;
            }
            to[j] = c1;
            i++;
            j++;
        }
        // Handling the end.
        if (i == elems-1) {
            to[j] = from[i];
            j++;
            i++;
        }
        elems = j;
        char* t = to;
        to = from;
        from = t;

    } while(changed);

    return elems;
}

int main() {

    FILE *fp = fopen("input", "r");
    int c = fread(input, sizeof(char), INPUT, fp);

    struct timeval begin;
    gettimeofday(&begin, NULL);

    int e1 = ex1('\0');
    printf("ex1: %d\n", e1);

    int min = e1;

    for (char c = 'a'; c <= 'z'; c++) {
        int v = ex1(c);
        if (v < min) min = v;
    }
    printf("ex2: %d\n", min); 

    struct timeval end;
    gettimeofday(&end, NULL);
    int begint =  begin.tv_sec * (int)1e6 + begin.tv_usec;
    int endt =  end.tv_sec * (int)1e6 + end.tv_usec;

    printf("took %d us\n", endt - begint);

    return 0;

}
