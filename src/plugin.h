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

#ifndef METER_PLUGIN_PLUGIN_H
#define METER_PLUGIN_PLUGIN_H

#include "collector.h"
#include "param.h"

#define PLUGIN_NAME_SIZE 32

struct meter_plugin;

typedef int (*plugin_init_func_t)(struct meter_plugin *plugin);
typedef int (*plugin_start_func_t)(struct meter_plugin *plugin);
typedef int (*plugin_stop_func_t)(struct meter_plugin *plugin);
typedef int (*plugin_parameter_func_t)(struct meter_plugin *plugin, struct plugin_parameters *parameters);
typedef int (*plugin_collector_init_func_t)(struct meter_plugin *plugin, struct collector *collector);

enum event_type;

struct meter_plugin {
    char name[PLUGIN_NAME_SIZE+1];
    struct collector *collectors;
    plugin_init_func_t init;
    plugin_start_func_t start;
    plugin_parameter_func_t parameters;
    plugin_collector_init_func_t collector;
    plugin_stop_func_t stop;
};

typedef struct meter_plugin meter_plugin_t;

void plugin_name(meter_plugin_t *plugin, const char *name);

int plugin_run(meter_plugin_t *plugin);

#endif //METER_PLUGIN_PLUGIN_H
