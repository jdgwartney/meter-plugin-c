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

#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "plugin.h"

/** \brief Initializes the members of the meter_plugin structure
 *
 */
static void plugin_initialize(meter_plugin_t *plugin) {
    memset(plugin,'\0', sizeof(meter_plugin_t));
}

/** \brief Allocates a plugin structure and initializes
 *
 */
meter_plugin_t *plugin_create() {
    meter_plugin_t *plugin = malloc(sizeof(meter_plugin_t));
    assert(plugin);
    plugin_initialize(plugin);
    return plugin;
}

/** \brief Calls the plugin provided plugin init method if registered
 *
 */
int plugin_init(meter_plugin_t *plugin) {
    int result = 0;
    // If an initialization method has been registered call it
    if (plugin->init) {
        if (plugin->init(plugin)) {
            fprintf(stderr, "Plugin initialization function failed\n");
            result = 1;
        }
    }
    return result;
}

/** \brief Calls the plugin provided plugin start method if registered
 *
 */
int plugin_start(meter_plugin_t *plugin) {
    int result = 0;
    // If an start method has been registered call it
    if (plugin->start) {
        if (plugin->start(plugin)) {
            fprintf(stderr, "Plugin start function failed\n");
            result = 1;
        }
    }
    return result;
}

/** \brief Create collectors for each of the parameter items
 *
 */
void plugin_create_collectors(meter_plugin_t *plugin, plugin_parameters_t *parameters) {

    size_t size = parameters->size;
    plugin->collectors = malloc(sizeof(collector_ptr_t) * size);
    assert(plugin->collectors != NULL);

    for (int i = 0; i < size; i++) {
        parameter_item_t *items = parameters->items[i];
        char name[COLLECTOR_NAME_SIZE];
        sprintf(name, "collector #%d", i);
        collector_t *collector = collector_create(items);
        if (plugin->collector_init) {
            plugin->collector_init(plugin, collector);
        }
        plugin->collectors[i] = collector;
    }
}

/** \brief Calls the collector initialization method on each of the collectors
 *
 */
void plugin_init_collectors(meter_plugin_t *plugin) {
    size_t size = plugin->num_collectors;
    collector_ptr_t *collectors = plugin->collectors;

    for (size_t i = 0; i < size; i++) {
        collector_t *collector = collectors[i];
        collector_init(collector);
    }
}


/** \brief Calls the collector initialization method on each of the collectors
 *
 */
void plugin_start_collectors(meter_plugin_t *plugin) {
    size_t size = plugin->num_collectors;
    collector_ptr_t *collectors = plugin->collectors;

    for (size_t i = 0; i < size; i++) {
        collector_t *collector = collectors[i];
        collector_start(collector);
    }
}

/** /brief Main plugin function for processing measurements
 *
 */
int plugin_run(meter_plugin_t *plugin) {

    // Initialize the plugin
    if (plugin_init(plugin)) {
        exit(1);
    }

    // Start the plugin
    if (plugin_start(plugin)) {
        exit(1);
    }

    // Load the plugin configuration from "param.json"
    plugin_parameters_t *parameters = parameter_load(DEFAULT_PARAMETERS_PATH);
    assert(parameters != NULL);
    plugin->parameters = parameters;
    plugin->num_collectors = parameters->size;

    // If an param method has been registered call it
    if (plugin->param) {
        if (plugin->param(plugin)) {
            fprintf(stderr, "Plugin parameter function failed\n");
            exit(1);
        }
    }


    // Create a collector for each of plugin parameter "items"
    plugin_create_collectors(plugin, parameters);

    // Start each of the collectors by calling their start method
    plugin_start_collectors(plugin);

    int count = plugin->num_collectors;
    while (1) {
        // Loop through the collectors and call eaches respective collection method
        for (int i = 0; i < count; i++) {
            collector_t *collector = plugin->collectors[i];
            collector_collect(collector);
        }
        sleep(1);
    }
}
