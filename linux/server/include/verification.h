#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bellards.h"

#define VERIFYDIGITS 50

typedef struct {
    int start;
    int end;
} range;

// note for self: dont forget to init seed
int random(int start, int end){
    return start + rand() % (end - start + 1);
}

int verify(char* pi, range place) {
    int length = strlen(pi);
    if ((place.end - place.start + 1) != length) return 1;

    int counter = 0;

    for (int i = 0; i < VERIFYDIGITS; i++) {
        int cPlace = random(place.start, place.end);
        int bellardsDigit = computePi(cPlace);

        if (pi[cPlace - place.start] - '0' == bellardsDigit) {
            counter++;
        }
    }
    return (counter == VERIFYDIGITS) ? 0 : 1;
}
