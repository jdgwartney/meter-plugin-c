//
// Copyright 2016 BMC Software, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "measurement.h"

double rand_range(int min, int max) {
    double rnum =rand()/(double)RAND_MAX;
    return floor(rnum * ((max - min) + 1)) + min;
}

void measurement_initialize() {
    setvbuf(stdout, NULL, _IOLBF, 0);
    srand(time(NULL));
}

void measurement_get(MEASUREMENT *m) {
    strcpy(m->metric, "EXAMPLE_COUNT");
    m->value = rand_range(0, 99);
    strcpy(m->source,"foo");
    m->timestamp = time(NULL);
}

void measurement_output(MEASUREMENT *m) {
    printf("%s %.3f %s %ld\n", m->metric, m->value, m->source, m->timestamp);
}
