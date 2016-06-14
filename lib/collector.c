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

/** \brief Calls our collectors init method
 *
 */
void collector_init(collector_t *collector) {
    assert(collector);
    if (collector->init) {
        collector->init(collector);
    }
}

/** \brief Calls our collectors start method
 *
 */
void collector_start(collector_t *collector) {
    assert(collector);
    if (collector->start) {
        collector->start(collector);
    }
}

/** \brief Calls our collectors collect method
 *
 */
void collector_collect(collector_t *collector) {
    assert(collector);
    if (collector->collect) {
        collector->collect(collector);
    }
}


/**
 * /brief Create a collector object
 */
collector_t *collector_create(parameter_item_t *item) {
    collector_t *collector = malloc(sizeof(collector_t));
    assert(collector);
    memset(collector,'\0', sizeof(collector_t));
    collector->item = item;
    // Default the sink to standard out, specific plugins can override in the collector init method
    collector->send_measurement = measurement_get_sink(STDOUT);
    return collector;
}
