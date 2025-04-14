#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} range;

range getRange(int start, float score) {
    int max_factor = 10000; // scale number range size (0.1 = 1000)
    int end = start + (score * max_factor);

    r.start = start;
    r.end = end;
    return r;
}
