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
#ifndef METER_PLUGIN_MEASUREMENT_H
#define METER_PLUGIN_MEASUREMENT_H

#include <stdlib.h>
#include <time.h>

// Maximum size of a metric definition name
#define METRIC_NAME_MAX  128

// Maximum size of a source name
#define SOURCE_NAME_MAX 128

struct measurement {
    char metric[METRIC_NAME_MAX+1];
    double value;
    char source[SOURCE_NAME_MAX+1];
    time_t timestamp;
};

typedef struct measurement MEASUREMENT;

void measurement_get(MEASUREMENT *m);
void measurement_initialize();
void measurement_output(MEASUREMENT *m);

#endif //METER_PLUGIN_MEASUREMENT_H
