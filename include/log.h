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
#ifndef METER_PLUGIN_LOG_H
#define METER_PLUGIN_LOG_H

enum log_level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};


void llog(enum log_level level, char *msg);

#endif //METER_PLUGIN_LOG_H
