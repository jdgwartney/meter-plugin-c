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

// forward declaration
struct meter_plugin;

// Maximum size of a metric definition name
#define MEASUREMENT_METRIC_SIZE 128

// Maximum size of a source name
#define SOURCE_NAME_MAX 128

typedef char measurement_metric_t[MEASUREMENT_METRIC_SIZE];
typedef double measurement_value_t;
typedef char measurement_source_t[SOURCE_NAME_MAX];
typedef time_t measurement_timestamp_t;

struct measurement {
    measurement_metric_t metric;
    measurement_value_t value;
    measurement_source_t source;
    measurement_timestamp_t timestamp;
};

typedef struct measurement measurement_t;

enum measurement_sink_type {
    API,
    RPC,
    STDOUT
};


typedef void (*measurement_send_func)(measurement_metric_t metric,
                                      measurement_value_t value,
                                      measurement_source_t source,
                                      measurement_timestamp_t *timestamp);


// Private API
void measurement_initialize(struct meter_plugin *plugin);

// Public API
measurement_send_func measurement_get_sink(enum measurement_sink_type type);


#endif //METER_PLUGIN_MEASUREMENT_H
