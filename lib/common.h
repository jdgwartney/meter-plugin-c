#ifndef METER_PLUGIN_COMMON_H
#define METER_PLUGIN_COMMON_H

enum plugin_result {
    SUCCESS,
    FAIL
};

typedef enum plugin_result plugin_result_t;

double rand_range(int min, int max);

#endif //METER_PLUGIN_COMMON_H
