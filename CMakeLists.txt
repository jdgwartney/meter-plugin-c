cmake_minimum_required(VERSION 3.5)
project(meter_plugin)
# The version number.
set (meter_plugin_VERSION_MAJOR 1)
set (meter_plugin_VERSION_MINOR 0)

set(SOURCE_FILES main.c)
add_executable(meter-plugin ${SOURCE_FILES})