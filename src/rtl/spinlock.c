//
// Created by Neko on 28.02.2025.
//

#include "spinlock.h"

#include <ke/irql.h>

KERNEL_API void KiCreateSpinLock(
    PKSPINLOCK Spinlock) {
    Spinlock->Lock = SPINLOCK_UNLOCKED;
}

KERNEL_API void KiAcquireSpinlock(
    PKSPINLOCK Spinlock) {
    KIRQL CurrentIrql;
    KIRQL OldIrql = 0;
    
    // Raise IRQL if needed
    CurrentIrql = KeGetCurrentIrql();
    if (CurrentIrql < DEVICE_LEVEL) KeRaiseIrql(DEVICE_LEVEL, &OldIrql);

    while (Spinlock->Lock == SPINLOCK_LOCKED) {
        asm volatile ("pause"); // Self explanatory
    }

    // Lock
    Spinlock->Lock = SPINLOCK_LOCKED;

    // Restore old
    if (CurrentIrql < DEVICE_LEVEL) KeLowerIrql(OldIrql);
}


KERNEL_API void KiReleaseSpinlock(
    PKSPINLOCK Spinlock) {
    Spinlock->Lock = SPINLOCK_UNLOCKED;
}
