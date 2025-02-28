//
// Created by Neko on 28.02.2025.
//

#ifndef IO_H
#define IO_H

#include <kernel.h>

typedef ULONG IO_PORT_ATTRIBUTE;
typedef IO_PORT_ATTRIBUTE* PIO_PORT_ATTRIBUTE;

enum IO_PORT_ATTRIBUTES {
    IOP_ATTRIBUTE_READABLE = 1 << 0,
    IOP_ATTRIBUTE_WRITABLE = 1 << 1
};

struct IO_PORT_DESCRIPTOR {
    USHORT PortRangeStart;
    USHORT PortRangeEnd;
    enum IO_PORT_ATTRIBUTES PortAttributes;
};

typedef struct IO_PORT_DESCRIPTOR* PIO_PORT_DESCRIPTOR;

KERNEL_API void IoCreatePortResource(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    enum IO_PORT_ATTRIBUTES ulPortAttributes,
    USHORT usPortRangeStart,
    USHORT usPortRangeEnd
    );

KERNEL_API void IoDestroyPortResource(
    PIO_PORT_DESCRIPTOR pPortDescriptor);

KERNEL_API STATUS IoWritePortByte(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    UCHAR ucValue
    );

KERNEL_API STATUS IoReadPortByte(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PUCHAR pucValue
    );

KERNEL_API STATUS IoWritePortWord(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    USHORT usValue
    );

KERNEL_API STATUS IoReadPortWord(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PUSHORT pusValue
    );

KERNEL_API STATUS IoWritePortDword(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    ULONG ulValue
    );

KERNEL_API STATUS IoReadPortDword(
    PIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PULONG pulValue
    );

#endif //IO_H
