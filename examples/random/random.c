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

#define PARAM_FIELD_MAX "min"
#define PARAM_FIELD_MIN "max"
#define PARAM_FIELD_SOURCE "source"
#define PARAM_FIELD_INTERVAL "interval"

struct random_plugin {
    measurement_metric_t metric;
};

int random_start(meter_plugin_t *plugin) {
    fprintf(stderr, "example_start()\n");
    return 0;
}

int random_param(meter_plugin_t *plugin, struct plugin_parameters *parameters) {
    fprintf(stderr, "example_parameters()\n");
    size_t size = parameters->size;
    for (int i = 0 ; i < size ; i++) {
        param_integer_t host = parameter_get_integer(parameters->items[i], PARAM_FIELD_MIN);
        fprintf(stderr, "min: %lld\n", host);
        param_integer_t port = parameter_get_integer(parameters->items[i], PARAM_FIELD_MAX);
        fprintf(stderr, "max: %lld\n", port);
        param_string_t source = parameter_get_string(parameters->items[i], PARAM_FIELD_SOURCE);
        fprintf(stderr, "source: %s\n", source);
        param_integer_t interval = parameter_get_integer(parameters->items[i], PARAM_FIELD_INTERVAL);
        fprintf(stderr, "interval: %lld\n", interval);
    }

    return 0;
}

int random_collect(collector_t * collector) {
    measurement_timestamp_t timestamp = time(NULL);
    measurement_metric_t metric;
    fprintf(stderr, "collector: %s\n", collector->name);
    strcpy(metric, "EXAMPLE_COUNT");
    measurement_value_t value = rand_range(0, 99);
    measurement_source_t source = "foo";
    collector->send_measurement(metric, value, source, &timestamp);
    return 0;
}

int random_collect_init(meter_plugin_t *plugin, collector_t *collector) {
    fprintf(stderr, "collector name: %s\n", collector->name);
}

int main(int argc, char * argv[]) {
    meter_plugin_t * plugin = plugin_create();
    plugin->collect = random_collect;
    plugin->collect_init = random_collect_init;
    plugin->param = random_param;
    return plugin_run(plugin);
}
