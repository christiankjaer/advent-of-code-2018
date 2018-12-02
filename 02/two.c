#include <stdio.h>
#include <sys/time.h>

#define STRLEN 26
#define LINELEN (STRLEN + 1)
#define INPLEN 250

char file[LINELEN*INPLEN];

void ex1() {
    int f2 = 0;
    int f3 = 0;

    for (int i = 0; i < INPLEN; i++) {
        char* p = &file[i*LINELEN];
        int counts[STRLEN] = {0};
        for (int i = 0; i < STRLEN; i++) counts[p[i] - 'a']++;
        int c2 = 0;
        int c3 = 0;
        for (int i = 0; i < STRLEN; i++) {
            if (counts[i] == 3) c3 |= 1; 
            else if (counts[i] == 2) c2 |= 1;
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
                if (p[i] != q[i]) diff++;
                if (diff > 1) break;
            }
            if (diff == 1) {
                prints(p, q);
                return;
            }
        }
    }
}

void ex_fused() {

    char *p; char *q;
    int f2 = 0;
    int f3 = 0;
    int done = 0;

    for (int i = 0; i < INPLEN; i++) {
        p = &file[i*LINELEN];

        /// EX 1
        int counts[STRLEN] = {0};
        for (int i = 0; i < STRLEN; i++) counts[p[i] - 'a']++;
        int c2 = 0;
        int c3 = 0;
        for (int i = 0; i < STRLEN; i++) {
            if (counts[i] == 3) c3 |= 1; 
            else if (counts[i] == 2) c2 |= 1;
        }
        f2 += c2;
        f3 += c3;

        /// EX 2
        if (done) continue;

        for (int j = i + 1; j < INPLEN; j++) {
            q = &file[j*LINELEN];
            int diff = 0;
            for (int i = 0; i < STRLEN; i++) {
                if (p[i] != q[i]) diff++;
                if (diff > 1) break;
            }
            if (diff == 1) {
                prints(p, q);
                done = 1;
                break;
            }
        }
    }
    printf("ex1. answer = %d\n", f2 * f3);

}

int main() {

    FILE *f = fopen("input", "rb");
    fread(file, 1, LINELEN*INPLEN, f);

    struct timeval begin;
    gettimeofday(&begin, NULL);
    
    // ex1();
    // ex2();
    ex_fused();

    struct timeval end;
    gettimeofday(&end, NULL);
    int begint =  begin.tv_sec * (int)1e6 + begin.tv_usec;
    int endt =  end.tv_sec * (int)1e6 + end.tv_usec;

    printf("took %d us\n", endt - begint);

    return 0;
}
