//
// Created by Neko on 28.02.2025.
//

#include "io.h"

#include <ke/error.h>

static BOOL KiIsIoPortValid(PKIO_PORT_DESCRIPTOR pPortDescriptor, USHORT usPort)
{
    if (!(pPortDescriptor->PortRangeStart <= usPort && pPortDescriptor->PortRangeEnd >= usPort))
    {
        return FALSE;
    }

    return TRUE;
}

static BOOL KiIsIoPortReadable(PKIO_PORT_DESCRIPTOR pPortDescriptor)
{
    return pPortDescriptor->PortAttributes & IOP_ATTRIBUTE_READABLE;
}

static BOOL KiIsIoPortWritable(PKIO_PORT_DESCRIPTOR pPortDescriptor)
{
    return pPortDescriptor->PortAttributes & IOP_ATTRIBUTE_WRITABLE;
}

KERNEL_API void KiCreatePortResource(PKIO_PORT_DESCRIPTOR PortDescriptor, KIO_PORT_ATTRIBUTE PortAttributes,
                                     USHORT PortRangeStart, USHORT PortRangeEnd)
{
    PortDescriptor->PortAttributes = PortAttributes;
    PortDescriptor->PortRangeStart = PortRangeStart;
    PortDescriptor->PortRangeEnd = PortRangeEnd;
}

KERNEL_API void KiDestroyPortResource(PKIO_PORT_DESCRIPTOR PortDescriptor)
{
    PortDescriptor->PortAttributes = 0UL;
    PortDescriptor->PortRangeStart = 0x0000;
    PortDescriptor->PortRangeEnd = 0x0000;
}

KERNEL_API STATUS KiWritePortByte(PKIO_PORT_DESCRIPTOR PortDescriptor, USHORT Port, UCHAR Value)
{
    if (!KiIsIoPortValid(PortDescriptor, Port))
    {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortWritable(PortDescriptor))
    {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    __asm__ __volatile__("outb %1, %0" : : "dN"(Port), "a"(Value));

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS KiReadPortByte(PKIO_PORT_DESCRIPTOR PortDescriptor, USHORT Port, PUCHAR Value)
{
    if (!KiIsIoPortValid(PortDescriptor, Port))
    {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortReadable(PortDescriptor))
    {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    UCHAR ReadValue;

    __asm__ __volatile__("inb %1, %0" : "=a"(ReadValue) : "dN"(Port));

    *Value = ReadValue;

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS KiWritePortWord(PKIO_PORT_DESCRIPTOR PortDescriptor, USHORT Port, USHORT Value)
{
    if (!KiIsIoPortValid(PortDescriptor, Port))
    {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortWritable(PortDescriptor))
    {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    __asm__ __volatile__("outw %1, %0" : : "dN"(Port), "a"(Value));

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS KiReadPortWord(PKIO_PORT_DESCRIPTOR PortDescriptor, USHORT Port, PUSHORT Value)
{
    if (!KiIsIoPortValid(PortDescriptor, Port))
    {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortReadable(PortDescriptor))
    {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    USHORT ReadValue;

    __asm__ __volatile__("inw %1, %0" : "=a"(ReadValue) : "dN"(Port));

    *Value = ReadValue;

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS KiWritePortDword(PKIO_PORT_DESCRIPTOR PortDescriptor, USHORT Port, ULONG Value)
{
    if (!KiIsIoPortValid(PortDescriptor, Port))
    {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortWritable(PortDescriptor))
    {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    __asm__ __volatile__("outl %1, %0" : : "dN"(Port), "a"(Value));

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

KERNEL_API STATUS KiReadPortDword(PKIO_PORT_DESCRIPTOR PortDescriptor, USHORT Port, PULONG Value)
{
    if (!KiIsIoPortValid(PortDescriptor, Port))
    {
        SetLastError(STATUS_OUT_OF_BOUNDS);
        return STATUS_OUT_OF_BOUNDS;
    }

    if (!KiIsIoPortReadable(PortDescriptor))
    {
        SetLastError(STATUS_DENIED);
        return STATUS_DENIED;
    }

    ULONG ReadValue;

    __asm__ __volatile__("inl %1, %0" : "=a"(ReadValue) : "dN"(Port));

    *Value = ReadValue;

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}
