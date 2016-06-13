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
#ifndef METER_PLUGIN_EXAMPLE_H
#define METER_PLUGIN_EXAMPLE_H

#include "plugin.h"

#define PARAM_FIELD_HOST "host"
#define PARAM_FIELD_PORT "port"
#define PARAM_FIELD_SOURCE "source"
#define PARAM_FIELD_INTERVAL "interval"

int example_parameters(meter_plugin_t *plugin, struct plugin_parameters *parameters);
int example_start(meter_plugin_t *plugin);
int example_collect(collector_t *collector);

#endif //METER_PLUGIN_EXAMPLE_H
