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
#include "collector.h"

void collector_collect(collector_t *collector) {

    collector->collect(collector);
}


/**
 * /brief Create a collector object
 */
collector_t *collector_create(const char * name,
                              parameter_item_t *item,
                              measurement_send_func send,
                              collector_collect_func collect) {
    collector_t *collector = malloc(sizeof(collector_t));
    assert(collector);
    strcpy(collector->name, name);
    collector->item = item;
    collector->collect = collect;
    collector->send_measurement = send;
    return collector;
}
