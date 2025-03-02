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
#include <kdbg/debug_print.h>
#include <mm/physical.h>

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


#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

void *memmove(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *--d = *--s;
        }
    }
    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1, *p2 = s2;
    while (n--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}
#ifdef __cplusplus
}
#endif



#define PAGE_SIZE 4096

static void* heap_end = NULL;
static intptr_t allocated_size = 0;

void* sbrk(intptr_t increment) {
    static void* program_break = NULL;

    if (program_break == NULL) {
        MmAllocatePage(&program_break);
        heap_end = program_break;
    }

    if (increment == 0) {
        return program_break;
    }

    void* old_break = program_break;

    if (increment > 0) {
        intptr_t required_size = allocated_size + increment;
        
        while (required_size > (heap_end - program_break)) {
            void* new_page;
            MmAllocatePage(&new_page);
            heap_end = (char*)heap_end + PAGE_SIZE;
        }

        allocated_size += increment;
        program_break = (char*)program_break + increment;

    } else {
        if (allocated_size + increment < 0) {
            KeDebugPrint("sbrk: trying to free too much memory\n");
            return (void*)-1;
        }

        allocated_size += increment;
        program_break = (char*)program_break + increment;

        while ((heap_end - program_break) >= PAGE_SIZE) {
            heap_end = (char*)heap_end - PAGE_SIZE;
            MmFreePage(heap_end);
        }
    }
    KeDebugPrint("sbrk: old break %p, new break %p\n", old_break, program_break);

    return old_break;
}

