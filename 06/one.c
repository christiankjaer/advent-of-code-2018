#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#define INPUT 360

#define MIN(a,b) (((a)<(b))?(a):(b))

int data[INPUT][INPUT];
int tmp[INPUT][INPUT];

static inline int p(int v1, int v2) {
    return v1 == v2 || v2 == 0;
}

int main() {

    struct timeval begin;
    gettimeofday(&begin, NULL);
    
    char *line = NULL;
    size_t len;

    FILE *fp = fopen("input", "r");

    int i = 1;
    int maxx = 0;
    int maxy = 0;
    while (getline(&line, &len, fp) != -1) {
        int x, y;
        sscanf(line, "%d, %d", &x, &y);
        maxx = (x > maxx) ? x : maxx;
        maxy = (y > maxy) ? y : maxy;
        data[y][x] = i++;
    }

    int elems = i;

    int changed;

    do {
        changed = 0;
        for (int y = 1; y <= maxy; y++) {
            for (int x = 1; x <= maxx; x++) {
                if (data[y][x] != 0) {
                    tmp[y][x] = data[y][x];
                    continue;
                }
                int u = data[y][x-1];
                int d = data[y][x+1];
                int l = data[y-1][x];
                int r = data[y+1][x];

                int v = 0;
                changed = 1;

                if (u != 0) {
                    v = (p(u,l) && p(u,d) && p(u,r)) ? u : -1;
                } else if (l != 0) {
                    v = (p(l,u) && p(l,d) && p(l,r)) ? l : -1;
                } else if (d != 0) {
                    v = (p(d,u) && p(d,l) && p(d,r)) ? d : -1;
                } else if (r != 0) {
                    v = (p(r,u) && p(r,l) && p(r,d)) ? r : -1;
                }

                tmp[y][x] = v;
            }
        }
        memcpy(data, tmp, INPUT*INPUT*sizeof(int));
    } while (changed);

    int* hist = calloc(elems, sizeof(int));

    for (int y = 1; y <= maxy; y++) {
        for (int x = 1; x <= maxx; x++) {
            hist[data[y][x]]++;
        }
    }


    int max = 0;
    // Skip the edges
    for (int x = 1; x <= maxx; x++) {
        hist[data[1][x]] = 0;
        hist[data[maxy][x]] = 0;
    }
    // Skip the edges
    for (int y = 1; y <= maxy; y++) {
        hist[data[y][1]] = 0;
        hist[data[y][maxx]] = 0;
    }
    for (int i = 1; i <= elems; i++) {
        max = (hist[i] > max) ? hist[i] : max;
    }
    printf("ex1: %d\n", max);

    struct timeval end;
    gettimeofday(&end, NULL);
    int begint =  begin.tv_sec * (int)1e6 + begin.tv_usec;
    int endt =  end.tv_sec * (int)1e6 + end.tv_usec;

    printf("took %d us\n", endt - begint);

    free(line);
    free(hist);
    fclose(fp);

    return 0;

}
