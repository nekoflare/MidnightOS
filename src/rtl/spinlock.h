//
// Created by Neko on 28.02.2025.
//

#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <kernel.h>

enum KSPINLOCK_LOCK_STATE {
    SPINLOCK_LOCKED,
    SPINLOCK_UNLOCKED
};

struct KSPINLOCK {
    volatile enum KSPINLOCK_LOCK_STATE Lock;
};

typedef struct KSPINLOCK* PKSPINLOCK;

KERNEL_API void KiCreateSpinLock(
    PKSPINLOCK Spinlock);

KERNEL_API void KiAcquireSpinlock(
    PKSPINLOCK Spinlock);

KERNEL_API void KiReleaseSpinlock(
    PKSPINLOCK Spinlock);

#endif //SPINLOCK_H
