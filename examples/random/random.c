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

#include <stdio.h>
#include <string.h>
#include <time.h>

#define PARAM_FIELD_HOST "host"
#define PARAM_FIELD_PORT "port"
#define PARAM_FIELD_SOURCE "source"
#define PARAM_FIELD_INTERVAL "interval"

int example_parameters(meter_plugin_t *plugin, struct plugin_parameters *parameters);
int example_start(meter_plugin_t *plugin);
int example_collect(collector_t *collector);

int example_start(meter_plugin_t *plugin) {
    fprintf(stderr, "example_start()\n");
    return 0;
}

int example_parameters(meter_plugin_t *plugin, struct plugin_parameters *parameters) {
    fprintf(stderr, "example_parameters()\n");
    param_string_t host = parameter_get_string(parameters->items[0], PARAM_FIELD_HOST);
    fprintf(stderr, "host: %s\n", host);
    param_integer_t port = parameter_get_integer(parameters->items[0], PARAM_FIELD_PORT);
    fprintf(stderr, "port: %lld\n", port);
    param_string_t source = parameter_get_string(parameters->items[0], PARAM_FIELD_SOURCE);
    fprintf(stderr, "source: %s\n", source);
    param_integer_t interval = parameter_get_integer(parameters->items[0], PARAM_FIELD_INTERVAL);
    fprintf(stderr, "interval: %lld\n", interval);

    return 0;
}

int example_collect(collector_t * collector) {
    measurement_timestamp_t timestamp = time(NULL);
    measurement_metric_t metric;
    strcpy(metric, "EXAMPLE_COUNT");
    measurement_value_t value = rand_range(0, 99);
    measurement_source_t source = "foo";
    collector->send_measurement(metric, value, source, &timestamp);
    return 0;
}

int main(int argc, char * argv[]) {
    meter_plugin_t * plugin = plugin_create();
    return plugin_run(plugin);
}
