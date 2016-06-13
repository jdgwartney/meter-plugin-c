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
#ifndef METER_PLUGIN_COLLECTOR_H
#define METER_PLUGIN_COLLECTOR_H

#include "measurement.h"
#include "param.h"

#define COLLECTOR_NAME_SIZE 32

struct collector;

typedef int (*collector_collect_func)(struct collector *collector);
typedef int (*collector_start_func)(struct collector *collector);

struct collector {
    char name[COLLECTOR_NAME_SIZE];
    parameter_item_t * item;
    measurement_send_func send_measurement;
    collector_collect_func collect;
    collector_start_func start;
};

typedef struct collector collector_t;
typedef collector_t * collector_ptr_t;

//
// Private API
//

void collector_collect(collector_t *collector);
void collector_start(collector_t *collector);

//
// Public API
//

collector_t * collector_create(const char * name,
                               parameter_item_t *item,
                               measurement_send_func send,
                               collector_collect_func collect);


#endif //METER_PLUGIN_COLLECTOR_H
