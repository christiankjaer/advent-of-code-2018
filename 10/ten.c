
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <limits.h>
        
#define N 391

typedef struct {
    int x;
    int y; 
    int x_vel;
    int y_vel;
} particle;

particle sol[N];

void print() {
    int min_x = INT_MAX;
    int min_y = INT_MAX;
    int max_x = INT_MIN;
    int max_y = INT_MIN;
    for (int i = 0; i < N; i++) {
        particle p = sol[i];
        if (p.x < min_x) min_x = p.x;
        if (p.y < min_y) min_y = p.y;
        if (p.x > max_x) max_x = p.x;
        if (p.y > max_y) max_y = p.y;
    }

    int res[max_x - min_x + 1][max_y - min_y + 1];

    for (int x = 0; x < max_x - min_x + 1; x++) {
        for (int y = 0; y < max_y - min_y + 1; y++) {
            res[x][y] = 0;
        }
    }


    for (int i = 0; i < N; i++) {
        particle p = sol[i];
        int x = p.x - min_x;
        int y = p.y - min_y;
        res[x][y] = 1;
    }

    for (int y = 0; y < max_y - min_y + 1; y++) {
        for (int x = 0; x < max_x - min_x + 1; x++) {
            if (res[x][y]) putchar('#');
            else putchar(' ');
        }
        putchar('\n');
    }

}

int done() {
    for (int i = 0; i < N; i++) {
        int has_neighbor = 0;
        particle p1 = sol[i];
        for (int j = 0; j < N; j++) {
            particle p2 = sol[j];
            if (i != j && abs(p1.x - p2.x) <= 1 && abs(p1.y - p2.y) <= 1) {
                has_neighbor = 1; break;
            }
        }
        if (!has_neighbor) return 0;
    }
    return 1;
}

void step() {
    for (int i = 0; i < N; i++) {
        particle p = sol[i];
        sol[i].x += p.x_vel;
        sol[i].y += p.y_vel;
    }
}

int main() {

    FILE *fp = fopen("input", "r");
    char *line = NULL;
    size_t len;
    int i = 0;

    while (getline(&line, &len, fp) != -1) {
        sscanf(line, "position=< %d, %d> velocity=< %d, %d>", &sol[i].x, &sol[i].y, &sol[i].x_vel, &sol[i].y_vel);
        i++;
    }

    struct timeval begin;
    gettimeofday(&begin, NULL);
    i = 0;

    while(!done()) {
        i++;
        step();
    }

    print();
    printf("its: %d\n", i);

    struct timeval end;
    gettimeofday(&end, NULL);
    int begint =  begin.tv_sec * (int)1e6 + begin.tv_usec;
    int endt =  end.tv_sec * (int)1e6 + end.tv_usec;

    printf("took %d us\n", endt - begint);
    return 0;

}
