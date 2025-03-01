//
// Created by Neko on 28.02.2025.
//

#define NANOPRINTF_IMPLEMENTATION
#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 1
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
