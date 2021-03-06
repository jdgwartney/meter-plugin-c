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
#include <stdio.h>
#include <time.h>
#include "measurement.h"

/** \brief Sets the file to line level buffering
 *
 */
static void measurement_set_line_buffering(FILE *file) {
    setvbuf(file, NULL, _IOLBF, 0);
}

/** \brief Writes measurements via API calls
 *
 */
static void measurement_api_sink(measurement_metric_t metric,
                                 measurement_value_t value,
                                 measurement_source_t source,
                                 measurement_timestamp_t *timestamp) {
    assert(1);
}

/** \brief Writes measurements via Meter RPC calls
 *
 */
static void measurement_rpc_sink(measurement_metric_t metric,
                                 measurement_value_t value,
                                 measurement_source_t source,
                                 measurement_timestamp_t *timestamp) {
    assert(1);
}

/** \brief Writes measurements via Standard Out to Plugin Manager
 *
 */
static void measurement_stdout_sink(measurement_metric_t metric,
                                    measurement_value_t value,
                                    measurement_source_t source,
                                    measurement_timestamp_t *timestamp) {
    // Metric and Source are required so assert if they are not provided
    assert(metric);
    assert(source);

    // If we have a time stamp then write it with the measurement
    if (timestamp) {
        printf("%s %.3f %s %ld\n", metric, value, source, *timestamp);
    } else {
        printf("%s %.3f %s\n", metric, value, source);
    }
}

// Array of send measurement sinks, for easy look up by measurement_sink_type
static measurement_send_func measurement_sinks[] = {
        measurement_api_sink,
        measurement_rpc_sink,
        measurement_stdout_sink
};

/** \brief Returns a function pointer to the specified measurement sink
 *
 */
measurement_send_func measurement_get_sink(enum measurement_sink_type type) {

    // If the standard out sink is selected than set the standard out stream
    // to line buffered. Otherwise the measurements will show up randomly
    if (type == STDOUT) {
        measurement_set_line_buffering(stdout);
    }
    return measurement_sinks[type];
}






