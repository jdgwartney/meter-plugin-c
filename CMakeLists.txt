cmake_minimum_required(VERSION 3.5)
project(meter_plugin)

set(SOURCE_FILES src/main.c)
add_executable(plugin ${SOURCE_FILES})