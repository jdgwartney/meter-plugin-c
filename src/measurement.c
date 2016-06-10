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
#include "measurement.h"

void measurement_initialize() {
    setvbuf(stdout, NULL, _IOLBF, 0);
    srand(1234);
}

void measurement_get(MEASUREMENT *m) {
    strcpy(m->metric, "EXAMPLE_COUNT");
    double r = rand();
    double n = r/RAND_MAX;
    m->value = n;
    strcpy(m->source,"foo");
    m->timestamp = time(NULL);
}

void measurement_output(MEASUREMENT *m) {
    printf("%s %f %s %ld\n", m->metric, m->value, m->source, m->timestamp);
}
