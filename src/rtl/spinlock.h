//
// Created by Neko on 28.02.2025.
//

#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <kernel.h>

enum SPINLOCK_LOCK_STATE {
    SPINLOCK_LOCKED,
    SPINLOCK_UNLOCKED
};

struct SPINLOCK {
    volatile enum SPINLOCK_LOCK_STATE Lock;
};

typedef struct SPINLOCK* PSPINLOCK;

KERNEL_API void RtlCreateSpinLock(
    PSPINLOCK Spinlock);

KERNEL_API void RtlAcquireSpinlock(
    PSPINLOCK Spinlock);

KERNEL_API void RtlReleaseSpinlock(
    PSPINLOCK Spinlock);

#endif //SPINLOCK_H
