//
// Created by Neko on 05.03.2025.
//

#ifndef MANAGER_H
#define MANAGER_H

#include <kernel.h>
#include <se/descriptor.h>

/* TODO: those two functions, PSID* will point to a pointer that will hold the Sid, IdentifierAuthority is who owns this SID, e.g: NT_AUTHORITY. */

STATUS CreateSid(
    PSID* Sid,
    ULONG IdentifierAuthority,
    ULONG* SubAuthorities,
    UCHAR SubAuthorityCount);


STATUS SeCreateSecurityDescriptor(
    PSECURITY_DESCRIPTOR* SecurityDescriptor,
    PSID Owner,
    PSID Group,
    PACL Dacl,
    PACL Sacl);

#endif //MANAGER_H
