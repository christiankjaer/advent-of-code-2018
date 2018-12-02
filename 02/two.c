#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#define STRLEN 26
#define LINELEN (STRLEN + 1)
#define INPLEN 250

char file[LINELEN*INPLEN];

void ex1() {
    int f2 = 0;
    int f3 = 0;
    int counts[STRLEN];
    char* p;

    for (int i = 0; i < INPLEN; i++) {
        p = &file[i*LINELEN];
        memset(&counts[0], 0, sizeof(int)*STRLEN);

        for (int i = 0; i < STRLEN; i++) counts[p[i] - 'a']++;
        int c2 = 0;
        int c3 = 0;
        for (int i = 0; i < STRLEN; i++) {
            int d3 = counts[i] == 3;
            int d2 = counts[i] == 2 && !d3;
            c2 |= d2;
            c3 |= d3;
        }
        f2 += c2;
        f3 += c3;
    }
    printf("ex1. answer = %d\n", f2 * f3);
}

void prints(char* s, char* t) {
    for (int i = 0; i < STRLEN; i++) {
        if (s[i] == t[i])
            putchar(s[i]);
    }
    putchar('\n');
}

void ex2() {
    char *p; char *q;
    for (int i = 0; i < INPLEN - 1; i++) {
        p = &file[i * LINELEN];
        for (int j = i + 1; j < INPLEN; j++) {
            q = &file[j * LINELEN];
            int diff = 0;
            for (int i = 0; i < STRLEN; i++) {
                diff += (p[i] != q[i]);
            }
            if (diff == 1) {
                prints(p, q);
                return;
            }
        }
    }
}

int main() {

    FILE *f = fopen("input", "rb");
    fread(file, 1, LINELEN*INPLEN, f);

    struct timeval begin;
    gettimeofday(&begin, NULL);
    
    ex1();
    ex2();

    struct timeval end;
    gettimeofday(&end, NULL);
    int begint =  begin.tv_sec * (int)1e6 + begin.tv_usec;
    int endt =  end.tv_sec * (int)1e6 + end.tv_usec;

    printf("took %d us\n", endt - begint);

    return 0;
}
