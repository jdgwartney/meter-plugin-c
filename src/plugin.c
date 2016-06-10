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

#include "plugin.h"
#include "measurement.h"
#include "param.h"
#include <stdio.h>
#include <unistd.h>

#define PARAM_FIELD_HOST "host"
#define PARAM_FIELD_PORT "port"
#define PARAM_FIELD_SOURCE "source"
#define PARAM_FIELD_INTERVAL "interval"

int plugin_run() {

    // Initialize the measurement services
    measurement_initialize();

    PLUGIN_PARAMETERS *parameters = parameter_load(DEFAULT_PARAMETERS_PATH);
    if (parameters == NULL) {
        exit(1);
    }
    PARAM_STRING host = parameter_get_string(parameters->items[0], PARAM_FIELD_HOST);
    fprintf(stderr, "host: %s\n", host);
    PARAM_INTEGER port = parameter_get_integer(parameters->items[0], PARAM_FIELD_PORT);
    fprintf(stderr, "port: %lld\n", port);
    PARAM_STRING source = parameter_get_string(parameters->items[0], PARAM_FIELD_SOURCE);
    fprintf(stderr, "source: %s\n", source);
    PARAM_INTEGER interval = parameter_get_integer(parameters->items[0], PARAM_FIELD_INTERVAL);
    fprintf(stderr, "interval: %lld\n", interval);

    while(1) {
        MEASUREMENT m;
        sleep(1);
        measurement_get(&m);
        measurement_output(&m);
    }
}
