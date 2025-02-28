//
// Created by Neko on 26.02.2025.
//

#ifndef CPU_H
#define CPU_H

#include <kernel.h>

KERNEL_API void KiExplicitHalt();
KERNEL_API void KiExplicitDisableInterrupts();
KERNEL_API void KiExplicitEnableInterrupts();

#endif //CPU_H
