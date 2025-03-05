//
// Created by Neko on 05.03.2025.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <kernel.h>
#include <rtl/linked_list.h>
#include <se/descriptor.h>

typedef struct _OBJECT_TYPE {
    LPSTR Name;
    ULONG ObjectSize;
    ULONG Flags;
    void (*DeleteProcedure)(PVOID Object);
    void (*SecurityProcedure)(PVOID Object, PSECURITY_DESCRIPTOR SecurityDescriptor);
} OBJECT_TYPE, *POBJECT_TYPE;

typedef struct _OBJECT_HEADER {
    ULONG ReferenceCount;
    ULONG HandleCount;
    POBJECT_TYPE ObjectType;
    PSECURITY_DESCRIPTOR SecurityDescriptor;
    PKLINKED_LIST ObjectListEntry;
} OBJECT_HEADER, *POBJECT_HEADER;

#endif //OBJECT_H
