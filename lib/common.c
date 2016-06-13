//
// Created by Gwartney, David on 6/10/16.
//
#include <math.h>
#include <stdlib.h>
#include "common.h"

/**
 * Initialize a collector object
 */
double rand_range(int min, int max) {
    double rnum =rand()/(double)RAND_MAX;
    return floor(rnum * ((max - min) + 1)) + min;
}
