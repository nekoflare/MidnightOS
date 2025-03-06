//
// Created by Neko on 28.02.2025.
//

#include <hal/io.h>
#include <rtl/spinlock.h>
#include <stdarg.h>

#include "debug_print.h"

KERNEL_API void KiDebugConnPuts(LPSTR lpszMsg);

#define DEBUG_PORT 0xE9

static struct KSPINLOCK slDebugPrint;
static struct KIO_PORT_DESCRIPTOR ipdDebugPort;

KERNEL_API void KiDebugConnPuts(LPSTR lpszMsg)
{
    for (; *lpszMsg != '\0'; lpszMsg++)
    {
        KiWritePortByte(&ipdDebugPort, 0xE9, *lpszMsg);
    }
}

KERNEL_API void KiInitializeDebugPort()
{
    PREVENT_DOUBLE_INIT
    KiCreateSpinLock(&slDebugPrint);
    KiCreatePortResource(&ipdDebugPort, IOP_ATTRIBUTE_WRITABLE, DEBUG_PORT, DEBUG_PORT);
}

KERNEL_API void KeDebugPrint(LPSTR lpszMsg, ...)
{
    KiAcquireSpinlock(&slDebugPrint);

    va_list args;
    va_start(args, lpszMsg);

    // Format the log message.
    CHAR MessageBuffer[1024];
    vsnprintf(MessageBuffer, sizeof(MessageBuffer), lpszMsg, args);
    KiDebugConnPuts(MessageBuffer);

    va_end(args);
    KiReleaseSpinlock(&slDebugPrint);
}

KERNEL_API void KeDebugPrintNoSync(LPSTR lpszMsg, ...)
{
    va_list args;
    va_start(args, lpszMsg);

    // Format the log message.
    CHAR MessageBuffer[1024];
    vsnprintf(MessageBuffer, sizeof(MessageBuffer), lpszMsg, args);
    KiDebugConnPuts(MessageBuffer);

    va_end(args);
}