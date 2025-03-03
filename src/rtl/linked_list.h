//
// Created by Neko on 28.02.2025.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <kernel.h>

struct KLINKED_LIST;
struct KLINKED_LIST_ENTRY;
typedef struct KLINKED_LIST_ENTRY* PKLINKED_LIST_ENTRY;
typedef struct KLINKED_LIST* PKLINKED_LIST;

struct KLINKED_LIST {
    SIZE_T EntryCount;
    PKLINKED_LIST_ENTRY Front;
    PKLINKED_LIST_ENTRY Back;
};

struct KLINKED_LIST_ENTRY
{
    PVOID Data;
    PKLINKED_LIST_ENTRY Front;
    PKLINKED_LIST_ENTRY Back;
};

KERNEL_API void KiCreateLinkedList(
    PKLINKED_LIST LinkedList);

KERNEL_API void KiPushToLinkedList(
    PKLINKED_LIST LinkedList,
    PVOID Data);

KERNEL_API PVOID KiPushFromLinkedList(
    PKLINKED_LIST LinkedList);

KERNEL_API SIZE_T KiGetLinkedListEntryCount(
    PKLINKED_LIST LinkedList);

KERNEL_API PVOID KiPopFromLinkedListAt(
    PKLINKED_LIST LinkedList,
    SIZE_T Index);

KERNEL_API void KiPushToLinkedListAt(
    PKLINKED_LIST LinkedList,
    PVOID Data,
    SIZE_T Index);

#endif //LINKED_LIST_H
