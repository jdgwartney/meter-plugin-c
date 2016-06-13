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

#include <string.h>
#include <unistd.h>
#include "common.h"
#include "plugin.h"
#include "event.h"
#include "metric.h"
#include "measurement.h"
#include "param.h"

int plugin_collect(collector_t *collector) {
    measurement_timestamp_t timestamp = time(NULL);
    measurement_metric_t metric;
    strcpy(metric, "EXAMPLE_COUNT");
    measurement_value_t value = rand_range(0, 99);
    measurement_source_t source = "foo";
    collector->send_measurement(metric, value, source, &timestamp);
    return 0;
}

/** \brief Initializes the members of the meter_plugin structure
 *
 */
static void plugin_initialize(struct meter_plugin *plugin) {
    plugin->name[0] = '\0';
    plugin->collectors = NULL;
    plugin->num_collectors = 0;
    plugin->init = NULL;
    plugin->start = NULL;
    plugin->parameters = NULL;
    plugin->collector = NULL;
    plugin->stop = NULL;
}

meter_plugin_t *plugin_create() {
    meter_plugin_t *plugin = malloc(sizeof(meter_plugin_t));
    plugin_initialize(plugin);
}

void plugin_set_name(meter_plugin_t *plugin, const char *name) {
    strcpy(plugin->name, name);
}

void plugin_set_handler() {

}

void plugin_create_collectors(meter_plugin_t *plugin, plugin_parameters_t *parameters) {
    size_t count = parameters->count;
    plugin->collectors = malloc(sizeof(collector_t * ) * count);

    for (int i = 0; i < count; i++) {
        parameter_item_t *items = parameters->items[i];
        char name[COLLECTOR_NAME_SIZE];
        sprintf(name, "%s - %d", "collector - ", i);
        collector_t *collector = collector_create(name,
                                                  items,
                                                  measurement_get_sink(STDOUT),
                                                  plugin_collect);
        plugin->collectors[i] = collector;
    }
}

int plugin_run(struct meter_plugin *plugin) {

    plugin_initialize(plugin);

    if (plugin->start) {
        plugin->start(plugin);
    }

    plugin_parameters_t *parameters = parameter_load(DEFAULT_PARAMETERS_PATH);
    if (parameters == NULL) {
        exit(1);
    }

    plugin_create_collectors(plugin, parameters);

    int count = parameters->count;
    while (1) {
        for (int i = 0; i < count; i++) {
            collector_t *collector = plugin->collectors[i];
            collector_collect(collector);
        }
        sleep(1);
    }
}
