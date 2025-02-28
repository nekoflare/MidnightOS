//
// Created by Neko on 26.02.2025.
//

#ifndef GDT_H
#define GDT_H

#include <kernel.h>

struct GDTR {
    USHORT Size;
    ULONGLONG GdtAddress;
} __attribute__((packed));
typedef struct GDTR* PGDTR;

struct GDT_ACCESS_BYTE {
    UCHAR Accessed        : 1;
    UCHAR ReadWrite       : 1;
    UCHAR Direction       : 1;
    UCHAR Executable      : 1;
    UCHAR DescriptorType  : 1;
    UCHAR DescriptorPrivLevel : 2;
    UCHAR Present         : 1;
} __attribute__((packed));
typedef struct GDT_ACCESS_BYTE* PGDT_ACCESS_BYTE;

enum GDT_ACCESS_BYTE_BITS
{
    GDT_ACCESSED_BIT = 1 << 0,
    GDT_READ_WRITE_BIT = 1 << 1,
    GDT_DIRECTION_BIT = 1 << 2,
    GDT_EXECUTABLE_BIT = 1 << 3,
    GDT_DESCRIPTOR_TYPE_BIT = 1 << 4,
    GDT_DPL0 = 0,
    GDT_DPL1 = 1 << 5,
    GDT_DPL2 = 1 << 6,
    GDT_DPL3 = (1 << 5) | (1 << 6),
    GDT_PRESENT = 1 << 7
};

enum GDT_FLAGS_BITS
{
    GDT_GRANULARITY_FLAG = 1 << 3,
    GDT_SIZE_FLAG = 1 << 2,
    GDT_LONG_MODE_FLAG = 1 << 1
};

struct GDT_SEGMENT_DESCRIPTOR {
    USHORT LimitLow;
    USHORT BaseLow;
    UCHAR BaseMiddle;
    UCHAR Access;
    UCHAR Limit : 4;
    UCHAR Flags : 4;
    UCHAR BaseHigh;
};

typedef struct GDT_SEGMENT_DESCRIPTOR* PGDT_SEGMENT_DESCRIPTOR;

struct GDT_SYSTEM_SEGMENT_DESCRIPTOR
{
    USHORT LimitLow;
    USHORT BaseLow;
    UCHAR BaseMiddle;
    UCHAR Access;
    UCHAR LimitHigh : 4;
    UCHAR Flags : 4;
    UCHAR BaseHigh;
    ULONG BaseUpper;
} __attribute__((packed));

typedef struct GDT_SYSTEM_SEGMENT_DESCRIPTOR* PGDT_SYSTEM_SEGMENT_DESCRIPTOR;

KERNEL_API void KiInitializeGDT();
KERNEL_API void KiFlushGDT(PGDTR gdtr);

#define GDT_ENTRY(_Base, _Limit, _Access, _Flags)                                                                      \
{                                                                                                                  \
    .LimitLow = (USHORT)(_Limit & 0xFFFF), .BaseLow = (USHORT)(_Base & 0xFFFF),       \
    .BaseMiddle = (UCHAR)((_Base & 0xFF0000) >> 16), .Access = _Access,                            \
    .Flags = _Flags,                              \
    .BaseHigh = (UCHAR)((_Base & 0xFF000000) >> 24)                                                 \
}

#endif //GDT_H
