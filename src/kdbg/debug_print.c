//
// Created by Neko on 28.02.2025.
//

#include <rtl/spinlock.h>
#include <hal/io.h>
#include <stdarg.h>

#include "debug_print.h"

KERNEL_API void KiDebugConnPuts(LPSTR lpszMsg);

#define DEBUG_CONN_IO_PORT 0xE9

static struct SPINLOCK slDebugPrint;
static struct IO_PORT_DESCRIPTOR ipdDebugPort;

KERNEL_API void KiDebugConnPuts(LPSTR lpszMsg)
{
    for (; *lpszMsg != '\0'; lpszMsg++)
    {
        IoWritePortByte(&ipdDebugPort, 0xE9, *lpszMsg);
    }
}

KERNEL_API void KiInitializeDebugPort() {
    RtlCreateSpinLock(&slDebugPrint);
    IoCreatePortResource(&ipdDebugPort, IOP_ATTRIBUTE_WRITABLE, DEBUG_CONN_IO_PORT, DEBUG_CONN_IO_PORT);
}

KERNEL_API void KeDebugPrint(LPSTR lpszMsg, ...) {
    RtlAcquireSpinlock(&slDebugPrint);

    va_list args;
    va_start(args, lpszMsg);

    // Format the log message.
    char message_buffer[1024];
    vsnprintf(message_buffer, sizeof(message_buffer), lpszMsg, args);
    KiDebugConnPuts(message_buffer);

    va_end(args);
    RtlReleaseSpinlock(&slDebugPrint);
}

KERNEL_API void KeDebugPrintNoSync(LPSTR lpszMsg, ...) {
    va_list args;
    va_start(args, lpszMsg);

    // Format the log message.
    char message_buffer[1024];
    vsnprintf(message_buffer, sizeof(message_buffer), lpszMsg, args);
    KiDebugConnPuts(message_buffer);

    va_end(args);
}