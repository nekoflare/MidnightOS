//
// Created by Neko on 28.02.2025.
//

#ifndef BUGCHECK_H
#define BUGCHECK_H

#include <kernel.h>

typedef ULONG BUGCHECK_REASON;

#define IRQL_LESS_OR_EQUAL 0

KERNEL_API LPSTR StringifyBugCheckError(BUGCHECK_REASON BugCheckReason);
KERNEL_API void KeBugCheck(BUGCHECK_REASON BugCheckReason);

#endif //BUGCHECK_H
