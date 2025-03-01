//
// Created by Neko on 28.02.2025.
//

#include "io.h"

#include <ke/error.h>

static BOOL KiIsIoPortValid(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort) {
    if (!(pPortDescriptor->PortRangeStart <= usPort && pPortDescriptor->PortRangeEnd >= usPort)) {
        return FALSE;
    }

    return TRUE;
}

static BOOL KiIsIoPortReadable(
    PIO_PORT_DESCRIPTOR pPortDescriptor) {
    return pPortDescriptor->PortAttributes & IOP_ATTRIBUTE_READABLE;
}

static BOOL KiIsIoPortWritable(
    PIO_PORT_DESCRIPTOR pPortDescriptor) {
    return pPortDescriptor->PortAttributes & IOP_ATTRIBUTE_WRITABLE;
}

KERNEL_API void IoCreatePortResource(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    IO_PORT_ATTRIBUTE ulPortAttributes,
    USHORT usPortRangeStart,
    USHORT usPortRangeEnd
)
{
    pPortDescriptor->PortAttributes = ulPortAttributes;
    pPortDescriptor->PortRangeStart = usPortRangeStart;
    pPortDescriptor->PortRangeEnd   = usPortRangeEnd;
}

KERNEL_API void IoDestroyPortResource(
    PIO_PORT_DESCRIPTOR pPortDescriptor) {
    pPortDescriptor->PortAttributes = 0UL;
    pPortDescriptor->PortRangeStart = 0x0000;
    pPortDescriptor->PortRangeEnd   = 0x0000;
}

KERNEL_API STATUS IoWritePortByte(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    UCHAR ucValue
    ) {
    if (!KiIsIoPortValid(pPortDescriptor, usPort)) {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortWritable(pPortDescriptor)) {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    __asm__ __volatile__ (
        "outb %1, %0"
        :
        : "dN" (usPort), "a" (ucValue)
    );

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS IoReadPortByte(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PUCHAR pucValue
    ) {
    if (!KiIsIoPortValid(pPortDescriptor, usPort)) {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortReadable(pPortDescriptor)) {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    UCHAR ucReadValue;

    __asm__ __volatile__ (
        "inb %1, %0"
        : "=a" (ucReadValue)
        : "dN" (usPort)
    );

    *pucValue = ucReadValue;

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS IoWritePortWord(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    USHORT usValue
    ) {
    if (!KiIsIoPortValid(pPortDescriptor, usPort)) {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortWritable(pPortDescriptor)) {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    __asm__ __volatile__ (
        "outw %1, %0"
        :
        : "dN" (usPort), "a" (usValue)
    );

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS IoReadPortWord(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PUSHORT pusValue
    ) {
    if (!KiIsIoPortValid(pPortDescriptor, usPort)) {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortReadable(pPortDescriptor)) {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    USHORT usReadValue;

    __asm__ __volatile__ (
        "inw %1, %0"
        : "=a" (usReadValue)
        : "dN" (usPort)
    );

    *pusValue = usReadValue;

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS IoWritePortDword(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    ULONG ulValue
    ) {
    if (!KiIsIoPortValid(pPortDescriptor, usPort)) {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortWritable(pPortDescriptor)) {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    __asm__ __volatile__ (
        "outl %1, %0"
        :
        : "dN" (usPort), "a" (ulValue)
    );

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS IoReadPortDword(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PULONG pulValue
    ) {
    if (!KiIsIoPortValid(pPortDescriptor, usPort)) {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortReadable(pPortDescriptor)) {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    ULONG ulReadValue;

    __asm__ __volatile__ (
        "inl %1, %0"
        : "=a" (ulReadValue)
        : "dN" (usPort)
    );

    *pulValue = ulReadValue;

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}
