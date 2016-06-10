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

#include "plugin.h"
#include "measurement.h"
#include "param.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void initialize() {
    setvbuf(stdout, NULL, _IOLBF, 0);
}

void get_measurement(MEASUREMENT *m) {
    strcpy(m->metric, "EXAMPLE_COUNT");
    m->value = 1;
    strcpy(m->source,"foo");
    m->timestamp = time(NULL);
}

int plugin_run(int argc, char * argv[]) {

    initialize();

    PLUGIN_PARAMETERS *param = get_parameters(DEFAULT_PARAMETERS_PATH);
    if (param == NULL) {
        exit(1);
    }

    while(1) {
        MEASUREMENT m;
        sleep(1);
        get_measurement(&m);
        measurement_output(&m);
    }
}
