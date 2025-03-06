//
// Created by Neko on 28.02.2025.
//

#include "linked_list.h"

#include "dlmalloc.h"

KERNEL_API void KiCreateLinkedList(PKLINKED_LIST LinkedList)
{
    if (!LinkedList)
        return;
    LinkedList->EntryCount = 0;
    LinkedList->Front = NULL;
    LinkedList->Back = NULL;
}

KERNEL_API void KiPushToLinkedList(PKLINKED_LIST LinkedList, PVOID Data)
{
    if (!LinkedList)
        return;

    PKLINKED_LIST_ENTRY NewEntry = malloc(sizeof(struct KLINKED_LIST_ENTRY));
    if (!NewEntry)
        return;

    NewEntry->Data = Data;
    NewEntry->Front = NULL;
    NewEntry->Back = LinkedList->Back;

    if (LinkedList->Back)
    {
        LinkedList->Back->Front = NewEntry;
    }
    else
    {
        LinkedList->Front = NewEntry;
    }

    LinkedList->Back = NewEntry;
    LinkedList->EntryCount++;
}

KERNEL_API PVOID KiPushFromLinkedList(PKLINKED_LIST LinkedList)
{
    if (!LinkedList || !LinkedList->Back)
        return NULL;

    PKLINKED_LIST_ENTRY Entry = LinkedList->Back;
    PVOID Data = Entry->Data;

    LinkedList->Back = Entry->Back;
    if (LinkedList->Back)
    {
        LinkedList->Back->Front = NULL;
    }
    else
    {
        LinkedList->Front = NULL;
    }

    free(Entry);
    LinkedList->EntryCount--;
    return Data;
}

KERNEL_API SIZE_T KiGetLinkedListEntryCount(PKLINKED_LIST LinkedList)
{
    if (!LinkedList)
        return 0;
    return LinkedList->EntryCount;
}

KERNEL_API PVOID KiPopFromLinkedListAt(PKLINKED_LIST LinkedList, SIZE_T Index)
{
    if (!LinkedList || Index >= LinkedList->EntryCount)
        return NULL;

    PKLINKED_LIST_ENTRY Entry = LinkedList->Front;
    for (SIZE_T i = 0; i < Index; i++)
    {
        Entry = Entry->Front;
    }

    if (!Entry)
        return NULL;

    if (Entry->Back)
    {
        Entry->Back->Front = Entry->Front;
    }
    else
    {
        LinkedList->Back = Entry->Front;
    }

    if (Entry->Front)
    {
        Entry->Front->Back = Entry->Back;
    }
    else
    {
        LinkedList->Front = Entry->Back;
    }

    PVOID Data = Entry->Data;
    free(Entry);
    LinkedList->EntryCount--;
    return Data;
}

KERNEL_API void KiPushToLinkedListAt(PKLINKED_LIST LinkedList, PVOID Data, SIZE_T Index)
{
    if (!LinkedList || Index > LinkedList->EntryCount)
        return;

    PKLINKED_LIST_ENTRY NewEntry = malloc(sizeof(struct KLINKED_LIST_ENTRY));
    if (!NewEntry)
        return;

    NewEntry->Data = Data;

    if (Index == 0)
    {
        NewEntry->Front = LinkedList->Front;
        NewEntry->Back = NULL;
        if (LinkedList->Front)
        {
            LinkedList->Front->Back = NewEntry;
        }
        else
        {
            LinkedList->Back = NewEntry;
        }
        LinkedList->Front = NewEntry;
    }
    else
    {
        PKLINKED_LIST_ENTRY PrevEntry = LinkedList->Front;
        for (SIZE_T i = 0; i < Index - 1; i++)
        {
            PrevEntry = PrevEntry->Front;
        }
        NewEntry->Front = PrevEntry->Front;
        NewEntry->Back = PrevEntry;
        if (PrevEntry->Front)
        {
            PrevEntry->Front->Back = NewEntry;
        }
        else
        {
            LinkedList->Back = NewEntry;
        }
        PrevEntry->Front = NewEntry;
    }

    LinkedList->EntryCount++;
}
