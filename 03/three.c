
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int x;
    int y; 
    int width;
    int height;
} rect;

int sol[1000][1000];

int main() {

    FILE *fp = fopen("input", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    rect rects[1401];
    while ((read = getline(&line, &len, fp)) != -1) {
        int x, y, height, width, i;
        sscanf(line, "#%d @ %d,%d: %dx%d", &i, &x, &y, &width, &height);
        rects[i-1].x = x;
        rects[i-1].y = y;
        rects[i-1].width = width;
        rects[i-1].height = height;
        for (int i = x; i < x + width; i++)
            for (int j = y; j < y + height; j++)
                sol[i][j]++;
    }

    int res = 0;

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (sol[i][j] > 1)
                res++;
        }
    }

    printf("ex1: %d\n", res);

    for (int i = 0; i < 1401; i++) {
        rect r = rects[i];
        int s = 1;
        for (int x = r.x; x < r.x + r.width; x++) {
            for (int y = r.y; y < r.y + r.height; y++) {
                if (sol[x][y] != 1) s = 0;
            }
        }
        if (s) printf("ex2: %d\n", i+1);
    }
    return 0;

}
