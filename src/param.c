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
#include <stdlib.h>

#include "param.h"

#define PARAM_FIELD_ITEMS "items"

void parameter_initialize(meter_plugin_t *plugin) {

}

void print_json_type(FILE *file, int json_type) {
    PLUGIN_PARAMETERS *p = malloc(sizeof(PLUGIN_PARAMETERS));

    switch(json_type) {
        case JSON_OBJECT:
            fprintf(file, "JSON_OBJECT");
            break;
        case JSON_ARRAY:
            fprintf(file, "JSON_ARRAY");
            break;
        case JSON_STRING:
            fprintf(file, "JSON_STRING");
            break;
        case JSON_INTEGER:
            fprintf(file, "JSON_INTEGER");
            break;
        case JSON_REAL:
            fprintf(file, "JSON_REAL");
            break;
        case JSON_TRUE:
            fprintf(file, "JSON_TRUE");
            break;
        case JSON_FALSE:
            fprintf(file, "JSON_FALSE");
            break;
        case JSON_NULL:
            fprintf(file, "JSON_FALSE");
            break;
        default:
            fprintf(file, "Unknown type: %d", json_type);
    }

}

void print_json_error(FILE *file, json_error_t error) {
    fprintf(file, "text: %s, source: %s, line: %d, column: %d, position: %d\n",
            error.text, error.source, error.line, error.column, error.position);
}

PLUGIN_PARAMETERS * parameter_load(const char *path) {
    PLUGIN_PARAMETERS *p = malloc(sizeof(PLUGIN_PARAMETERS));
    json_t *json;
    json_error_t error;

    json = json_load_file(path, 0, &error);
    if(json) {
        json_t * items = json_object_get(json, PARAM_FIELD_ITEMS);
        items = json_incref(items);
        size_t count = json_array_size(items);

        p->count = count;
        p->items = malloc(sizeof(PARAMETER_ITEM_PTR) * count);
        assert(p->items);

        size_t index;
        json_t *value;

        json_array_foreach(items, index, value) {
            p->items[index] = json_incref(value);
        }
    }
    else {
        print_json_error(stderr, error);
    }
    return p;
}

PARAM_BOOLEAN parameter_get_boolean(PARAMETER_ITEM *item, const char *key) {
    json_t * json = json_object_get(item, key);
    assert(json);
    assert(json_typeof(json) == JSON_TRUE || json_typeof(json) == JSON_FALSE);
    return json_boolean_value(json);
}

PARAM_INTEGER parameter_get_integer(PARAMETER_ITEM *item, const char *key) {
    json_t * json = json_object_get(item, key);
    assert(json);
    assert(json_typeof(json) == JSON_INTEGER);
    return json_integer_value(json);
}

PARAM_REAL parameter_get_real(PARAMETER_ITEM *item, const char *key) {
    json_t * json = json_object_get(item, key);
    assert(json);
    assert(json_typeof(json) == JSON_REAL);
    return json_real_value(json);
}

PARAM_STRING parameter_get_string(PARAMETER_ITEM *item, const char *key) {
    json_t * json = json_object_get(item, key);
    assert(json);
    assert(json_typeof(json) == JSON_STRING);
    return json_string_value(json);
}
