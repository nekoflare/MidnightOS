//
// Created by Neko on 28.02.2025.
//

#define NANOPRINTF_IMPLEMENTATION
#define NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS 1
#define NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS 1
#include "npf/nanoprintf.h"
#include "runtime.h"
#include <kdbg/debug_print.h>
#include <mm/common.h>
#include <mm/physical.h>
#include <mm/virtual.h>
#include <mm/vmem-allocator.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int sprintf(char *str, const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        int result = npf_vsnprintf(str, SIZE_MAX, format, args);
        va_end(args);
        return result;
    }

    int snprintf(char *str, size_t size, const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        int result = npf_vsnprintf(str, size, format, args);
        va_end(args);
        return result;
    }

    int vsprintf(char *str, const char *format, va_list arg)
    {
        return npf_vsnprintf(str, SIZE_MAX, format, arg);
    }

    int vsnprintf(char *str, size_t size, const char *format, va_list arg)
    {
        return npf_vsnprintf(str, size, format, arg);
    }

    void *memcpy(void *dest, const void *src, size_t n)
    {
        char *d = dest;
        const char *s = src;
        while (n--)
        {
            *d++ = *s++;
        }
        return dest;
    }

    int strlen(const char *s)
    {
        int c = 0;
        while (*s != '\0')
        {
            c++;
        }
        return c;
    }

    void *memset(void *s, int c, size_t n)
    {
        unsigned char *p = s;
        while (n--)
        {
            *p++ = (unsigned char)c;
        }
        return s;
    }

    void *memmove(void *dest, const void *src, size_t n)
    {
        char *d = dest;
        const char *s = src;
        if (d < s)
        {
            while (n--)
            {
                *d++ = *s++;
            }
        }
        else
        {
            d += n;
            s += n;
            while (n--)
            {
                *--d = *--s;
            }
        }
        return dest;
    }

    int memcmp(const void *s1, const void *s2, size_t n)
    {
        const unsigned char *p1 = s1, *p2 = s2;
        while (n--)
        {
            if (*p1 != *p2)
            {
                return *p1 - *p2;
            }
            p1++;
            p2++;
        }
        return 0;
    }
#ifdef __cplusplus
}
#endif

// Global state for the kernel heap
#define KERNEL_HEAP_SIZE (32ULL * 1024 * 1024 * 1024) // 32GB

// These globals track our reserved and committed regions.
static void *KernelHeapReservedBase = NULL;
static void *KernelHeapReservedEnd = NULL;
static void *KernelHeapCommittedEnd = NULL;

// This variable tracks how much of the heap has been used
static intptr_t AllocatedSize = 0;

KERNEL_API void MiInitializeKernelHeap()
{
    // Reserve 32GB of virtual memory for the kernel heap.
    ULONGLONG ReservedAddress = 0;
    if (MmAllocateKernelVirtualMemory(&ReservedAddress, KERNEL_HEAP_SIZE) != STATUS_SUCCESS)
    {
        KeDebugPrint("Failed to reserve 32GB kernel heap memory\n");
        return;
    }
    KernelHeapReservedBase = (void *)ReservedAddress;
    KernelHeapReservedEnd = (char *)KernelHeapReservedBase + KERNEL_HEAP_SIZE;

    // Commit the first page.
    void *PhysicalPage = NULL;
    if (MmAllocatePage(&PhysicalPage) != STATUS_SUCCESS)
    {
        KeDebugPrint("Failed to allocate initial physical page for kernel heap\n");
        return;
    }
    void *PageMap = NULL;
    MiGetKernelPageMapAddressVirtual(&PageMap);
    MiMapPage(VMS_READ_WRITE | VMS_SUPERVISOR, 0, PhysicalPage, KernelHeapReservedBase, PageMap);

    // Set committed end to one page past the reserved base.
    KernelHeapCommittedEnd = (char *)KernelHeapReservedBase + PAGE_SIZE;
    KeDebugPrint("Kernel heap initialized at %p, size: %llu bytes\n", KernelHeapReservedBase, KERNEL_HEAP_SIZE);
}

/*
 * sbrk:
 *
 * Adjusts the program break (i.e. the end of the heap) within the reserved 32GB region.
 * On positive increments, it commits additional pages as needed.
 * On negative increments, it frees unneeded pages.
 */
void *sbrk(intptr_t increment)
{
    // Use a static variable to track the current break within the reserved region.
    static void *ProgramBreak = NULL;
    if (ProgramBreak == NULL)
    {
        if (KernelHeapReservedBase == NULL)
        {
            KeDebugPrint("sbrk: Kernel heap not initialized\n");
            return (void *)-1;
        }
        ProgramBreak = KernelHeapReservedBase;
    }

    if (increment == 0)
    {
        return ProgramBreak;
    }

    // Calculate the new break value.
    void *NewBreak = (char *)ProgramBreak + increment;
    // Check that the new break stays within the reserved region.
    if (NewBreak < KernelHeapReservedBase || NewBreak > KernelHeapReservedEnd)
    {
        KeDebugPrint("sbrk: Requested break %p is out of reserved heap bounds\n", NewBreak);
        return (void *)-1;
    }

    if (increment > 0)
    {
        // Commit additional pages if new_break exceeds the committed region.
        while (NewBreak > KernelHeapCommittedEnd)
        {
            void *PhysicalPage = NULL;
            if (MmAllocatePage(&PhysicalPage) != STATUS_SUCCESS)
            {
                KeDebugPrint("sbrk: Failed to allocate additional physical page\n");
                return (void *)-1;
            }
            void *Pagemap = NULL;
            MiGetKernelPageMapAddressVirtual(&Pagemap);
            MiMapPage(VMS_READ_WRITE | VMS_SUPERVISOR, 0, PhysicalPage, KernelHeapCommittedEnd, Pagemap);
            KernelHeapCommittedEnd = (char *)KernelHeapCommittedEnd + PAGE_SIZE;
        }
    }
    else
    {
        // Negative increment: Free pages if they are no longer needed.
        while (((char *)KernelHeapCommittedEnd - (char *)NewBreak) >= PAGE_SIZE)
        {
            KernelHeapCommittedEnd = (char *)KernelHeapCommittedEnd - PAGE_SIZE;
            MmFreePage(KernelHeapCommittedEnd);
        }
    }

    void *OldBreak = ProgramBreak;
    ProgramBreak = NewBreak;
    AllocatedSize += increment;
    return OldBreak;
}