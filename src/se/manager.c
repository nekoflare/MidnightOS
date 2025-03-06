//
// Created by Neko on 05.03.2025.
//

#include "manager.h"

#include <ke/error.h>
#include <rtl/dlmalloc.h>
#include <rtl/memory.h>

STATUS SeCreateSid(PSID *Sid, ULONG IdentifierAuthority, PULONG SubAuthorities, UCHAR SubAuthorityCount)
{

    SID *NewSid = RtlZeroMallocSafe(sizeof(SID));

    NewSid->IdentifierAuthority = IdentifierAuthority;
    NewSid->SubAuthority = SubAuthorities;
    NewSid->SubAuthorityCount = SubAuthorityCount;

    *Sid = NewSid;

    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

STATUS SeCreateSecurityDescriptor(PSECURITY_DESCRIPTOR *SecurityDescriptor, PSID Owner, PSID Group, PACL Dacl,
                                  PACL Sacl)
{
    PSECURITY_DESCRIPTOR NewSecurityDescriptor = RtlZeroMallocSafe(sizeof(SECURITY_DESCRIPTOR));

    if (!NewSecurityDescriptor)
    {
        SetLastError(STATUS_OUT_OF_MEMORY);
        return STATUS_OUT_OF_MEMORY;
    }

    if (!Dacl)
    {
        NewSecurityDescriptor->Control &= ~SE_DACL_PRESENT;
        NewSecurityDescriptor->Control |= SE_DACL_DEFAULTED;
        NewSecurityDescriptor->Dacl = NULL;
    }

    if (!Sacl)
    {
        NewSecurityDescriptor->Control &= ~SE_SACL_PRESENT;
        NewSecurityDescriptor->Control |= SE_SACL_DEFAULTED;
        NewSecurityDescriptor->Sacl = NULL;
    }

    if (!Owner)
    {
        NewSecurityDescriptor->Control |= SE_OWNER_DEFAULTED;
    }
    else
    {
        NewSecurityDescriptor->Control &= ~SE_OWNER_DEFAULTED;
        NewSecurityDescriptor->Owner = Owner;
    }

    if (!Group)
    {
        NewSecurityDescriptor->Control |= SE_GROUP_DEFAULTED;
    }
    else
    {
        NewSecurityDescriptor->Control &= ~SE_GROUP_DEFAULTED;
        NewSecurityDescriptor->Group = Group;
    }

    *SecurityDescriptor = NewSecurityDescriptor;
    SetLastError(STATUS_SUCCESS);
    return STATUS_SUCCESS;
}

void SeLockDacl(PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    SecurityDescriptor->Control |= SE_PROTECTED_DACL;
}

void SeUnlockDacl(PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    SecurityDescriptor->Control &= ~SE_PROTECTED_DACL;
}

void SeLockSacl(PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    SecurityDescriptor->Control |= SE_PROTECTED_SACL;
}

void SeUnlockSacl(PSECURITY_DESCRIPTOR SecurityDescriptor)
{
    SecurityDescriptor->Control &= ~SE_PROTECTED_SACL;
}