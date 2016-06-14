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
#include "common.h"
#include "event.h"
#include "param.h"
#include "measurement.h"
#include "metric.h"

#define PLUGIN_NAME_SIZE 32

struct meter_plugin;

typedef plugin_result_t (*plugin_initialize_cb_t)(struct meter_plugin *plugin);
typedef plugin_result_t (*plugin_start_cb_t)(struct meter_plugin *plugin);
typedef plugin_result_t (*plugin_stop_cb_t)(struct meter_plugin *plugin);
typedef plugin_result_t (*plugin_parameter_cb_t)(struct meter_plugin *plugin);
typedef plugin_result_t (*plugin_collector_initialize_cb_t)(struct meter_plugin *plugin, struct collector *collector);

struct meter_plugin {
    char name[PLUGIN_NAME_SIZE+1];

    plugin_parameters_t *parameters;

    collector_list_t collectors;

    void * user_data;

    plugin_initialize_cb_t initialize_cb;
    plugin_start_cb_t start_cb;
    plugin_stop_cb_t stop_cb;
    plugin_parameter_cb_t parameters_cb;
    plugin_collector_initialize_cb_t collector_initialize_cb;
};

typedef struct meter_plugin meter_plugin_t;

meter_plugin_t * plugin_create();

plugin_result_t plugin_run(meter_plugin_t *plugin);



#endif //METER_PLUGIN_PLUGIN_H
