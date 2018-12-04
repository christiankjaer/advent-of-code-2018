#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "khash.h"

#define INPUT 1085

char *robot_log[INPUT];

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
        line = NULL; len = 0;
    }

    qsort(robot_log, INPUT, sizeof(char*), compare);

    int guard;
    i = 0;
    while (i < INPUT) {
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

    // Sleep for most lazy guard
    int most = 0;
    // When he was least active
    int active;
    // Ex2
    // The most least active time
    int mostactive = 0;
    int guard2 = 0;
    // Iteration variables
    int* glist;
    int tguard;
    kh_foreach(sleep_map, tguard, glist, {
        int sleep = 0;
        int localactive = 0;
        for (int t = 0; t < 60; t++) {
            sleep += glist[t];
            // Ex 1
            if (glist[t] > glist[localactive]) localactive = t;
            // Ex 2
            if (glist[t] > glist[mostactive]) {
                guard2 = tguard;
                mostactive = t;
            }
        }
        // Ex 1
        if (sleep > most) {
            most = sleep; guard = tguard; active = localactive;
        }
    });

    printf("Ex 1: %d\n", guard * active);
    printf("Ex 2: %d\n", guard2 * mostactive);
    return 0;

}
