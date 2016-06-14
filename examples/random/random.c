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

#define METRIC_NAME "EXAMPLE_RANDOM"

#define RANDOM_PARAM_MAX "min"
#define RANDOM_PARAM_MIN "max"
#define RANDOM_PARAM_SOURCE "source"
#define RANDOM_PARAM_INTERVAL "interval"

#define RANDOM_FUNCTION_NAME(NAME) fprintf(stderr, "%s: line: %d, %s\n",(NAME), __LINE__, __PRETTY_FUNCTION__);

// Specific data for the Random Plugin
struct random_plugin_data {
    measurement_metric_t metric;
};

// Collector specific data for Random Collector
struct random_collector_data {
    measurement_metric_t metric;
    int min;
    int max;
    int interval;
};

/** \brief Random plugin initialization method
 *
 */
int random_plugin_init(meter_plugin_t *plugin) {
    RANDOM_FUNCTION_NAME(plugin->name)
    strcpy(plugin->name, "random");
    return 0;
}

int random_plugin_start(meter_plugin_t *plugin) {
    RANDOM_FUNCTION_NAME(plugin->name)
    return 0;
}

/** \brief Random plugin collector start method
 *
 */
int random_plugin_param(meter_plugin_t *plugin) {
    RANDOM_FUNCTION_NAME(plugin->name)
    plugin_parameters_t *parameters = plugin->parameters;

    size_t size = parameters->size;
    for (int i = 0 ; i < size ; i++) {
        param_integer_t host = parameter_get_integer(parameters->items[i], RANDOM_PARAM_MIN);
        fprintf(stderr, "min: %lld, ", host);
        param_integer_t port = parameter_get_integer(parameters->items[i], RANDOM_PARAM_MAX);
        fprintf(stderr, "max: %lld, ", port);
        param_string_t source = parameter_get_string(parameters->items[i], RANDOM_PARAM_SOURCE);
        fprintf(stderr, "source: %s, ", source);
        param_integer_t interval = parameter_get_integer(parameters->items[i], RANDOM_PARAM_INTERVAL);
        fprintf(stderr, "interval: %lld\n", interval);
    }

    return 0;
}

/** \brief Random plugin collector start method
 *
 */
int random_collector_init(meter_plugin_t *plugin) {
    RANDOM_FUNCTION_NAME(plugin->name)
    return 0;
}

/** \brief Random plugin collector start method
 *
 */
int random_collector_start(meter_plugin_t *plugin) {
    RANDOM_FUNCTION_NAME(plugin->name)
    return 0;
}

/** \brief This function collects measurements, in this specific case random numbers
 *
 */
int random_collector_collect(collector_t * collector) {
    RANDOM_FUNCTION_NAME(collector->name)
    measurement_timestamp_t timestamp = time(NULL);
    measurement_metric_t metric;
    strcpy(metric, METRIC_NAME);
    measurement_value_t value = rand_range(0, 99);
    measurement_source_t source = "foo";
    collector->send_measurement(metric, value, source, &timestamp);
    return 0;
}

/** \brief Called to initialize each of the collectors
 *
 */
int random_plugin_collector_init(meter_plugin_t *plugin, collector_t *collector) {
    RANDOM_FUNCTION_NAME(plugin->name)
    collector->init = random_collector_init;
    collector->start = random_collector_start;
    collector->collect = random_collector_collect;
}

/** \brief Plugin main() entry point
 *
 */
int main(int argc, char * argv[]) {
    // Create an instance of a plugin
    meter_plugin_t * plugin = plugin_create();

    // Assign function pointers that get called by the framework
    //    init - Initial function called when plugin_run() is called with the meter plugin instance
    //    param - Called after the plugin parameters are read
    //    collector_init - Called to initialize the collectors from the plugin parameter items
    //    start - Called just before starting the collectors
    plugin->init = random_plugin_init;
    plugin->param = random_plugin_param;
    plugin->collector_init = random_plugin_collector_init;
    plugin->start = random_plugin_start;

    return plugin_run(plugin);
}
