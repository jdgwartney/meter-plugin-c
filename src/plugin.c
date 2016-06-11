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
#include "plugin.h"
#include "example.h"
#include "event.h"
#include "metric.h"
#include "measurement.h"
#include "param.h"


#define PARAM_FIELD_HOST "host"
#define PARAM_FIELD_PORT "port"
#define PARAM_FIELD_SOURCE "source"
#define PARAM_FIELD_INTERVAL "interval"

static void plugin_initialize(struct meter_plugin *plugin) {

}

void plugin_set_name(struct meter_plugin *plugin, const char *name) {
    strcpy(plugin->name, name);
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

    collector_t * collector = collector_create("my collector",
                                               parameters->items[0],
                                               measurement_get_sink(STDOUT),
                                               example_collect);

    while(1) {
        collector_collect(collector);
        sleep(1);
    }
}
