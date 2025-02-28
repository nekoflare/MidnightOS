//
// Created by Neko on 28.02.2025.
//

#ifndef ERROR_H
#define ERROR_H

#include <kernel.h>

KERNEL_API LPSTR StringifyError(STATUS status);
KERNEL_API STATUS GetLastError();
KERNEL_API void SetLastError(STATUS status);

#endif //ERROR_H
