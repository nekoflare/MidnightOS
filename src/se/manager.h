//
// Created by Neko on 05.03.2025.
//

#ifndef MANAGER_H
#define MANAGER_H

#include <kernel.h>
#include <se/descriptor.h>

/* TODO: those two functions, PSID* will point to a pointer that will hold the Sid, IdentifierAuthority is who owns this SID, e.g: NT_AUTHORITY. */

STATUS SeCreateSid(
    PSID* Sid,
    ULONG IdentifierAuthority,
    PULONG SubAuthorities,
    UCHAR SubAuthorityCount);


STATUS SeCreateSecurityDescriptor(
    PSECURITY_DESCRIPTOR* SecurityDescriptor,
    PSID Owner,
    PSID Group,
    PACL Dacl,
    PACL Sacl);

void SeLockDacl(
    PSECURITY_DESCRIPTOR SecurityDescriptor);

void SeUnlockDacl(
    PSECURITY_DESCRIPTOR SecurityDescriptor);

void SeLockSacl(
    PSECURITY_DESCRIPTOR SecurityDescriptor);

void SeUnlockSacl(
    PSECURITY_DESCRIPTOR SecurityDescriptor);

#endif //MANAGER_H
