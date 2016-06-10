#
# Copyright 2016 BMC Software, Inc.
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

bin_PROGRAMS=plugin
plugin_SOURCES= \
src/main.c \
src/collector.c \
src/collector.h \
src/event.c \
src/event.h \
src/metric.c \
src/metric.h \
src/log.c \
src/log.h \
src/measurement.c \
src/measurement.h \
src/param.c \
src/param.h \
src/plugin.c \
src/plugin.h

AM_LDFLAGS = -lm -ljansson
