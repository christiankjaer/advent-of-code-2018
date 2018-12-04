#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include "khash.h"

char *robot_log[1085];
// An associative data structure would be better.

int compare(const void* s1, const void* s2) {
    // Sort by the data (first 17 chars)
    return memcmp(*(const char **) s1, *(const char **) s2, 17);
}
KHASH_MAP_INIT_INT(smap, int*);

int main() {

    khash_t(smap) *sleep_map = kh_init(smap);

    FILE *fp = fopen("input", "r");
    char *line = NULL;
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
            khint_t k;
            int retval;
            k = kh_put(smap, sleep_map, guard, &retval);
            if (retval != 0) {
                int *p = calloc(60, sizeof(int));
                kh_val(sleep_map, k) = p;
            }
            i++;
            continue;
        }
        // Hope that they are in pairs.
        int start, end;
        sscanf(&robot_log[i][15], "%d", &start); // Minute starts at byte 15
        sscanf(&robot_log[i+1][15], "%d", &end);
        int* stuff = kh_val(sleep_map, kh_get(smap, sleep_map, guard));
        for (int j = start; j < end; j++) {
            stuff[j]++;
        }
        i += 2;
    }

    int most = 0;
    int active;
    for (khint_t k = kh_begin(sleep_map); k != kh_end(sleep_map); ++k) {
        if (!kh_exist(sleep_map, k)) continue;
        int* glist = kh_val(sleep_map, k);
        int sleep = 0;
        int localactive = 0;
        for (int t = 0; t < 60; t++) {
            sleep += glist[t];
            if (glist[t] > glist[localactive]) localactive = t;
        }
        if (sleep > most) {
            most = sleep; guard = kh_key(sleep_map, k); active = localactive;
        }
    }

    printf("Ex 1: %d\n", guard * active);

    most = 0;
    guard = 0;
    for (khint_t k = kh_begin(sleep_map); k != kh_end(sleep_map); ++k) {
        if (!kh_exist(sleep_map, k)) continue;
        int* glist = kh_val(sleep_map, k);
        for (int t = 0; t < 60; t++) {
            if (glist[t] > glist[most]) {
                guard = kh_key(sleep_map, k); most = t;
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
