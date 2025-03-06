//
// Created by Neko on 05.03.2025.
//

#ifndef MANAGER_H
#define MANAGER_H

#include <kernel.h>
#include <se/descriptor.h>

/* TODO: those two functions, PSID* will point to a pointer that will hold the Sid, IdentifierAuthority is who owns this SID, e.g: NT_AUTHORITY. */

KERNEL_API STATUS SeCreateSid(
    PSID* Sid,
    ULONG IdentifierAuthority,
    PULONG SubAuthorities,
    UCHAR SubAuthorityCount);


KERNEL_API STATUS SeCreateSecurityDescriptor(
    PSECURITY_DESCRIPTOR* SecurityDescriptor,
    PSID Owner,
    PSID Group,
    PACL Dacl,
    PACL Sacl);

KERNEL_API void SeLockDacl(
    PSECURITY_DESCRIPTOR SecurityDescriptor);

KERNEL_API void SeUnlockDacl(
    PSECURITY_DESCRIPTOR SecurityDescriptor);

KERNEL_API void SeLockSacl(
    PSECURITY_DESCRIPTOR SecurityDescriptor);

KERNEL_API void SeUnlockSacl(
    PSECURITY_DESCRIPTOR SecurityDescriptor);

#endif //MANAGER_H
