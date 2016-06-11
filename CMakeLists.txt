cmake_minimum_required(VERSION 3.5)
project(meter_plugin)

set(SOURCE_FILES src/main.c src/event.c src/event.h src/measurement.h src/plugin.c src/plugin.h src/param.c src/param.h src/log.c src/log.h src/measurement.c src/metric.c src/metric.h src/example.c src/example.h src/collector.c src/collector.h src/common.c src/common.h)
add_executable(plugin ${SOURCE_FILES})