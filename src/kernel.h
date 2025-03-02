//
// Created by Neko on 26.02.2025.
//

#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stdio.h>
#include <wchar.h>

#ifdef __cplusplus
#define KERNEL_API extern "C"
#define ASSEMBLY // presumably there's a KERNEL_API before this
#endif

#ifndef __cplusplus
#define KERNEL_API
#define ASSEMBLY extern // presumably there's a KERNEL_API before this
#endif



#define CDECL_ATTR __attribute__((cdecl))
#define STDCALL_ATTR __attribute__((stdcall))
#define PACKED_ATTR __attribute__((packed))
#define NORETURN_ATTR __attribute__((noreturn))

#define struct_t typedef struct
#define union_t typedef union
#define enum_t typedef enum

// Azure's
typedef signed char            I8;
typedef unsigned char          U8;
typedef short                  I16;
typedef unsigned short         U16;
typedef int                    I32;
typedef unsigned int           U32;
typedef long long              I64;
typedef unsigned long long     U64;
typedef float                  F32;
typedef double                 F64;
typedef void*                  HANDLE;

typedef signed char            CHAR;
typedef unsigned char          UCHAR;
typedef short                  SHORT;
typedef unsigned short         USHORT;
typedef int                    INT;
typedef unsigned int           UINT;
typedef int32_t                LONG;
typedef uint32_t               ULONG;
typedef long long int          LONGLONG;
typedef unsigned long long int ULONGLONG;
typedef float                  FLOAT;
typedef double                 DOUBLE;
typedef long long              INT64;
typedef unsigned long long     UINT64;
typedef void*                  PVOID;
typedef const void*            PCVOID;
typedef __int128_t             INT128;
typedef __uint128_t            UINT128;

typedef signed char            *PCHAR;
typedef unsigned char          *PUCHAR;
typedef short                  *PSHORT;
typedef unsigned short         *PUSHORT;
typedef int                    *PINT;
typedef unsigned int           *PUINT;
typedef int32_t                *PLONG;
typedef uint32_t               *PULONG;
typedef long long int          *PLONGLONG;
typedef unsigned long long int *PULONGLONG;
typedef float                  *PFLOAT;
typedef double                 *PDOUBLE;
typedef long long              *PINT64;
typedef unsigned long long     *PUINT64;

// Boolean type and values
typedef int                    BOOL;
#define FALSE                   0
#define TRUE                    1

// Handle types
typedef void*                  HANDLE;
typedef void*                  HINSTANCE;
typedef void*                  HMODULE;
typedef void*                  LPVOID;
typedef const void*            LPCVOID;
typedef char*                  LPSTR;
typedef const char*            LPCSTR;
typedef wchar_t*               LPWSTR;
typedef const wchar_t*         LPCWSTR;

typedef size_t SIZE_T;
typedef ssize_t SSIZE_T;

typedef unsigned long STATUS;

#define STATUS_OUT_OF_MEMORY 11
#define STATUS_ABORTED 10
#define STATUS_NOT_SUPPORTED 9
#define STATUS_INVALID_HANDLE 8
#define STATUS_NOT_FOUND 7
#define STATUS_NOT_IMPLEMENTED 6
#define STATUS_DENIED 5
#define STATUS_INSUFFICIENT_RESOURCES 4
#define STATUS_INVALID_PARAMETER 3
#define STATUS_OUT_OF_BOUNDS 2
#define STATUS_FAILURE 1
#define STATUS_SUCCESS 0

#define ALIGN_UP(ptr, align) (((uintptr_t)(ptr) + (align) - 1) & ~((align) - 1))
#define ALIGN_DOWN(ptr, align) ((uintptr_t)(ptr) & ~((align) - 1))

#ifndef __cplusplus
#define CHECK_SIZEOF(type, expected_size) \
_Static_assert(sizeof(type) == (expected_size), "Size check failed")
#else // __cplusplus
#define CHECK_SIZEOF(type, expected_size) \
static_assert(sizeof(type) == (expected_size), "Size check failed")
#endif // __cplusplus

CHECK_SIZEOF(USHORT, 2);
CHECK_SIZEOF(ULONG, 4);
CHECK_SIZEOF(ULONGLONG, 8);

#endif //KERNEL_H
