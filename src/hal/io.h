//
// Created by Neko on 28.02.2025.
//

#ifndef IO_H
#define IO_H

#include <kernel.h>

typedef ULONG KIO_PORT_ATTRIBUTE;
typedef KIO_PORT_ATTRIBUTE* PKIO_PORT_ATTRIBUTE;

enum KIO_PORT_ATTRIBUTES {
    IOP_ATTRIBUTE_READABLE = 1 << 0,
    IOP_ATTRIBUTE_WRITABLE = 1 << 1
};

struct KIO_PORT_DESCRIPTOR {
    USHORT PortRangeStart;
    USHORT PortRangeEnd;
    enum KIO_PORT_ATTRIBUTES PortAttributes;
};

typedef struct KIO_PORT_DESCRIPTOR* PKIO_PORT_DESCRIPTOR;

KERNEL_API void KiCreatePortResource(
    PKIO_PORT_DESCRIPTOR pPortDescriptor,
    KIO_PORT_ATTRIBUTE ulPortAttributes,
    USHORT usPortRangeStart,
    USHORT usPortRangeEnd
    );

KERNEL_API void KiDestroyPortResource(
    PKIO_PORT_DESCRIPTOR pPortDescriptor);

KERNEL_API STATUS KiWritePortByte(
    PKIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    UCHAR ucValue
    );

KERNEL_API STATUS KiReadPortByte(
    PKIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PUCHAR pucValue
    );

KERNEL_API STATUS KiWritePortWord(
    PKIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    USHORT usValue
    );

KERNEL_API STATUS KiReadPortWord(
    PKIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PUSHORT pusValue
    );

KERNEL_API STATUS KiWritePortDword(
    PKIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    ULONG ulValue
    );

KERNEL_API STATUS KiReadPortDword(
    PKIO_PORT_DESCRIPTOR pPortDescriptor,
    USHORT usPort,
    PULONG pulValue
    );

#endif //IO_H
