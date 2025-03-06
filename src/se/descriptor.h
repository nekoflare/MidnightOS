//
// Created by Neko on 05.03.2025.
//

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <kernel.h>

typedef struct _SID {
    UCHAR SubAuthorityCount;   // Number of subauthorities in the SID
    ULONG IdentifierAuthority; // The authority that issued the SID
    PULONG SubAuthority;     // Array of subauthority values
} SID, *PSID;

typedef struct _ACL {
    USHORT AclSize;            // Size, in bytes, of the ACL
    USHORT AceCount;           // Number of ACEs in the ACL
    // ACEs follow
} ACL, *PACL;

typedef struct _ACL_HEADER {
    UCHAR AceType;
    UCHAR AceFlags;
    USHORT AceSize;
    // Ace data follows.
} ACL_HEADER, *PACL_HEADER;

typedef ULONG SECURITY_DESCRIPTOR_CONTROL;

#define SE_DACL_PRESENT         (1 << 0)  // Security descriptor contains DACL
#define SE_DACL_DEFAULTED        (1 << 1)  // DACL wasn't explicitly set, created by system
#define SE_SACL_PRESENT         (1 << 2)  // Security descriptor contains SACL
#define SE_SACL_DEFAULTED        (1 << 3)  // SACL was defaulted
#define SE_OWNER_DEFAULTED       (1 << 4)  // Owner SID was defaulted
#define SE_GROUP_DEFAULTED       (1 << 5)  // Group SID was defaulted
#define SE_PROTECTED_DACL        (1 << 6)  // DACL is protected (cannot be modified)
#define SE_PROTECTED_SACL        (1 << 7)  // SACL is protected (cannot be modified)

typedef struct _SECURITY_DESCRIPTOR {
    SECURITY_DESCRIPTOR_CONTROL Control;   // Control flags (e.g., DACL, SACL present)
    PSID                        Owner;     // Pointer to owner SID
    PSID                        Group;     // Pointer to group SID
    PACL                        Dacl;      // Pointer to DACL
    PACL                        Sacl;      // Pointer to SACL
} SECURITY_DESCRIPTOR, *PSECURITY_DESCRIPTOR;

/* INFO
 * DACL defines permissions, e.g: read, write, execute for users or groups. It can grant or deny permissions to specific userrs , groups or other security principals. If no DACL is present then full access is allowed. A DACL with explicit deny ACEs can override any granted ACEs.
 * SACL on the other hand is used to audit access attempts, read, writes, etc. It's used by sysadmins.
 */

#endif // DESCRIPTOR_H
