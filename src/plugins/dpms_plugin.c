#include "plugins/dpms_plugin.h"

uint32_t flutterpi_dpms_is_available() {
    return compositor_is_available_dpms(flutterpi->compositor);
}

// 0 => success, non-zero value => errno-style error
int32_t flutterpi_dpms_set(uint64_t value) {
    return compositor_set_dpms(flutterpi->compositor, value);
}

uint64_t flutterpi_dpms_get() {
    return compositor_get_dpms(flutterpi->compositor);
}