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
#ifndef METER_PLUGIN_PARAM_H
#define METER_PLUGIN_PARAM_H

#include <jansson.h>
#include "plugin.h"

#define PARAMETER_MAX_STRING 128

#define DEFAULT_PARAMETERS_PATH "./param.json"

typedef char PARAM_BOOLEAN;
typedef long long PARAM_INTEGER;
typedef double PARAM_REAL;
typedef const char * PARAM_STRING;

typedef json_t PARAMETER_ITEM;
typedef PARAMETER_ITEM * PARAMETER_ITEM_PTR;

struct plugin_parameters {
    size_t count;
    PARAMETER_ITEM_PTR *items;
};

typedef struct plugin_parameters PLUGIN_PARAMETERS;

PLUGIN_PARAMETERS * parameter_load(const char *path);

void parameter_initialize(meter_plugin_t *plugin);

PARAM_BOOLEAN parameter_get_boolean(PARAMETER_ITEM *item, const char *key);
PARAM_INTEGER parameter_get_integer(PARAMETER_ITEM *item, const char *key);
PARAM_REAL parameter_get_real(PARAMETER_ITEM *item, const char *key);
PARAM_STRING parameter_get_string(PARAMETER_ITEM *item, const char *key);


#endif //METER_PLUGIN_PARAM_H
