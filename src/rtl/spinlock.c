//
// Created by Neko on 28.02.2025.
//

#include "spinlock.h"

#include <ke/irql.h>

KERNEL_API void RtlCreateSpinLock(
    PSPINLOCK Spinlock) {
    Spinlock->Lock = SPINLOCK_UNLOCKED;
}

KERNEL_API void RtlAcquireSpinlock(
    PSPINLOCK Spinlock) {
    KIRQL OldIrql;
    KeRaiseIrql(DEVICE_LEVEL, &OldIrql);
    while (Spinlock->Lock == SPINLOCK_LOCKED) {
        asm volatile ("pause");
    }
    Spinlock->Lock = SPINLOCK_LOCKED;
    KeLowerIrql(OldIrql);
}

KERNEL_API void RtlReleaseSpinlock(
    PSPINLOCK Spinlock) {
    Spinlock->Lock = SPINLOCK_UNLOCKED;
}
