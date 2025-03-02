#ifndef STRING_H
#define STRING_H

#include <kernel.h>

KERNEL_API SIZE_T StrLen(const CHAR* str);
KERNEL_API BOOL StrCmp(const CHAR* str1, const CHAR* str2);
KERNEL_API CHAR* StrCpy(CHAR* dest, const CHAR* src);
KERNEL_API CHAR* StrCat(CHAR* dest, const CHAR* src);

#endif //STRING_H