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
#include "common.h"

#define COLLECTOR_NAME_SIZE 32

struct collector;

/** \brief Function pointer type for initializing a collector
 *
 */
typedef plugin_result_t (*collector_init_cb)(struct collector *collector);
typedef plugin_result_t (*collector_start_cb)(struct collector *collector);
typedef plugin_result_t (*collector_collect_cb)(struct collector *collector);

/** \brief Structure that implements a meter plugin collector
 *
 */
struct collector {
    char name[COLLECTOR_NAME_SIZE];
    parameter_item_t * item;

    void * data;

    measurement_send_func send_measurement;

    collector_init_cb initialize_cb;
    collector_start_cb start_cb;
    collector_collect_cb collect_cb;
};

typedef struct collector collector_t;
typedef collector_t * collector_ptr_t;

struct collector_list {
    collector_ptr_t *list;
    size_t size;
};

typedef struct collector_list collector_list_t;

//
// Private API
//

plugin_result_t collector_initialize(collector_t *collector);
plugin_result_t collector_start(collector_t *collector);
plugin_result_t collector_collect(collector_t *collector);

//
// Public API
//

collector_t * collector_create(parameter_item_t *item);

#endif //METER_PLUGIN_COLLECTOR_H
