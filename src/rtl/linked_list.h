//
// Created by Neko on 28.02.2025.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <kernel.h>

struct LINKED_LIST;
struct LINKED_LIST_ENTRY;
typedef struct LINKED_LIST_ENTRY* PLINKED_LIST_ENTRY;
typedef struct LINKED_LIST* PLINKED_LIST;

struct LINKED_LIST {
    SIZE_T EntryCount;
    PLINKED_LIST_ENTRY Front;
    PLINKED_LIST_ENTRY Back;
};

struct LINKED_LIST_ENTRY
{
    PVOID Data;
    PLINKED_LIST_ENTRY Front;
    PLINKED_LIST_ENTRY Back;
};

KERNEL_API void RtlCreateLinkedList(
    PLINKED_LIST LinkedList);

KERNEL_API void RtlPushToLinkedList(
    PLINKED_LIST LinkedList,
    PVOID Data);

KERNEL_API PVOID RtlPushFromLinkedList(
    PLINKED_LIST LinkedList);

KERNEL_API SIZE_T RtlGetLinkedListEntryCount(
    PLINKED_LIST LinkedList);

KERNEL_API PVOID RtlPopFromLinkedListAt(
    PLINKED_LIST LinkedList,
    SIZE_T Index);

KERNEL_API void RtlPushToLinkedListAt(
    PLINKED_LIST LinkedList,
    PVOID Data,
    SIZE_T Index);

#endif //LINKED_LIST_H
