//
// Created by Neko on 28.02.2025.
//

#ifndef IRQL_H
#define IRQL_H

#include <kernel.h>

typedef ULONG KIRQL;
typedef KIRQL* PKIRQL;

#define PASSIVE_LEVEL 0     // All interrupts can occur.
#define APC_LEVEL 1         // asynchronous procedure calls can be processed, execute functions in context of a thread for deferred work
#define DISPATCH_LEVEL 2    // Thread sched and synchronization, timers and software interrupts can occur.
#define DEVICE_LEVEL 3      // Hardware interrupts can only occur. For drivers,
#define HIGH_LEVEL 4        // No interrupts will occur, for critical tasks.

KERNEL_API LPSTR StringifyIrql(
    KIRQL Irql);

KERNEL_API void KeRaiseIrql(
    KIRQL NewIrql,
    PKIRQL OldIrql
);

KERNEL_API KIRQL KeGetCurrentIrql();

KERNEL_API void KeLowerIrql(
    KIRQL OldIrql);

#endif //IRQL_H
