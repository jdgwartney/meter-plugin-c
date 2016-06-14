cmake_minimum_required(VERSION 3.5)
project(meter_plugin)

set(SOURCE_FILES lib/event.c lib/event.h include/measurement.h lib/plugin.c include/plugin.h lib/param.c include/param.h lib/log.c include/log.h lib/measurement.c lib/metric.c include/metric.h lib/collector.c include/collector.h lib/common.c include/common.h)
add_executable(plugin ${SOURCE_FILES})