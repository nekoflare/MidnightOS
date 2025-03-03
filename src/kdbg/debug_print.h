//
// Created by Neko on 28.02.2025.
//

#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <kernel.h>

KERNEL_API void KiInitializeDebugPort();
KERNEL_API void KeDebugPrint(LPSTR lpszMsg, ...) __attribute__((format(printf, 1, 2)));
KERNEL_API void KeDebugPrintNoSync(LPSTR lpszMsg, ...) __attribute__((format(printf, 1, 2)));

#endif //DEBUG_PRINT_H
