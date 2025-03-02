#include "string.h"

KERNEL_API SIZE_T StrLen(const CHAR* str) {
    SIZE_T len = 0;
    while (str[len] != 0) {
        len++;
    }
    return len;
}

KERNEL_API BOOL StrCmp(const CHAR* str1, const CHAR* str2) {
    SIZE_T len1 = StrLen(str1);
    SIZE_T len2 = StrLen(str2);
    if (len1 != len2) {
        return FALSE;
    }
    for (SIZE_T i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

KERNEL_API CHAR* StrCpy(CHAR* dest, const CHAR* src) {
    SIZE_T len = StrLen(src);
    for (SIZE_T i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    dest[len] = 0;
    return dest;
}

KERNEL_API CHAR* StrCat(CHAR* dest, const CHAR* src) {
    SIZE_T len1 = StrLen(dest);
    SIZE_T len2 = StrLen(src);
    for (SIZE_T i = 0; i < len2; i++) {
        dest[len1 + i] = src[i];
    }
    dest[len1 + len2] = 0;
    return dest;
}