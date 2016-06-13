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

void measurement_initialize(struct meter_plugin *plugin) {
    setvbuf(stdout, NULL, _IOLBF, 0);
    srand(time(NULL));
}

static void measurement_api_sink(measurement_metric_t metric,
                                 measurement_value_t value,
                                 measurement_source_t source,
                                 measurement_timestamp_t *timestamp) {
    assert(1);
}


static void measurement_rpc_sink(measurement_metric_t metric,
                                 measurement_value_t value,
                                 measurement_source_t source,
                                 measurement_timestamp_t *timestamp) {
    assert(1);

}

static void measurement_stdout_sink(measurement_metric_t metric,
                                    measurement_value_t value,
                                    measurement_source_t source,
                                    measurement_timestamp_t *timestamp) {
    assert(metric);

    if (source && timestamp) {
        assert(source);
        printf("%s %.3f %s %ld\n", metric, value, source, *timestamp);
    } else if (source) {
        printf("%s %.3f %s\n", metric, value, source);
    }
}

static measurement_send_func measurement_sinks[] = {
        measurement_api_sink,
        measurement_rpc_sink,
        measurement_stdout_sink
};

measurement_send_func measurement_get_sink(enum measurement_sink_type type) {
    return measurement_sinks[type];
}






