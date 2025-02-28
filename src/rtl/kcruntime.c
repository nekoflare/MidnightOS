//
// Created by Neko on 28.02.2025.
//

#define NANOPRINTF_IMPLEMENTATION
#include "npf/nanoprintf.h"

#include <stdio.h>

int sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = npf_vsnprintf(str, SIZE_MAX, format, args);
    va_end(args);
    return result;
}

int snprintf(char *str, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = npf_vsnprintf(str, size, format, args);
    va_end(args);
    return result;
}

int vsprintf(char *str, const char *format, va_list arg) {
    return npf_vsnprintf(str, SIZE_MAX, format, arg);
}

int vsnprintf(char *str, size_t size, const char *format, va_list arg) {
    return npf_vsnprintf(str, size, format, arg);
}
