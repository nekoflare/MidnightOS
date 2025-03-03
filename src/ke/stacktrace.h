/*
File Creator: AzureianGH
File Name: stacktrace.h

Desc:
This is the main header for the stacktrace component.
*/

#ifndef STACKTRACE_H
#define STACKTRACE_H

#include <kernel.h>
KERNEL_API void KiStackTraceInit();
KERNEL_API void KeWalkStack(UINT max_frames);
KERNEL_API void KeStackTraceRegisterFunction(ULONGLONG address, CHAR* name);
KERNEL_API CHAR* KeStackTraceGetFunctionName(ULONGLONG address);
KERNEL_API void KeStackTraceRegDefaults();

#endif //STACKTRACE_H