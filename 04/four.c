
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int x;
    int y; 
    int width;
    int height;
} rect;

char *robot_log[1085];
// An associative data structure would be better.
int sleeps[4000][60];


int compare(const void* s1, const void* s2) {
    // Sort by the data (first 17 chars)
    return memcmp(*(const char **) s1, *(const char **) s2, 17);
}


int main() {

    FILE *fp = fopen("input", "r");
    char *line = NULL;
    rect rects[1401];
    size_t len;

    int i = 0;
    while (getline(&line, &len, fp) != -1) {
        robot_log[i++] = line;
        line = NULL;
        len = 0;
    }
    struct timeval begin;
    gettimeofday(&begin, NULL);

    qsort(robot_log, 1085, sizeof(char*), compare);


    int guard;
    i = 0;
    while (i < 1085) {
        // Skip the ids, but save it.
        if(sscanf(&robot_log[i][26], "%d", &guard) == 1) {
            i++;
            continue;
        }
        // Hope that they are in pairs.
        int start, end;
        sscanf(&robot_log[i][15], "%d", &start); // Minute starts at byte 15
        sscanf(&robot_log[i+1][15], "%d", &end);
        for (int j = start; j < end; j++) {
            sleeps[guard][j]++;
        }
        i += 2;
    }

    int most = 0;
    int active;
    guard = 0;
    for (int g = 0; g < 4000; g++) {
        int sleep = 0;
        int localactive = 0;
        for (int t = 0; t < 60; t++) {
            sleep += sleeps[g][t];
            if (sleeps[g][t] > sleeps[g][localactive]) localactive = t;
        }
        if (sleep > most) {
            most = sleep; guard = g; active = localactive;
        }
    }

    printf("Ex 1: %d\n", guard * active);

    most = 0;
    guard = 0;
    for (int g = 0; g < 4000; g++) {
        for (int t = 0; t < 60; t++) {
            if (sleeps[g][t] > sleeps[guard][most]) {
                guard = g; most = t;
            }
        }
    }

    printf("Ex 2: %d\n", guard * most);


    struct timeval end;
    gettimeofday(&end, NULL);
    int begint =  begin.tv_sec * (int)1e6 + begin.tv_usec;
    int endt =  end.tv_sec * (int)1e6 + end.tv_usec;

    printf("took %d us\n", endt - begint);
    return 0;

}
