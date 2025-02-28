//
// Created by Neko on 28.02.2025.
//

#include "error.h"

static STATUS lastStatus = STATUS_SUCCESS;

KERNEL_API LPSTR StringifyError(STATUS status) {
    switch (status) {
        case STATUS_SUCCESS:                return "STATUS_SUCCESS";
        case STATUS_FAILURE:                return "STATUS_FAILURE";
        case STATUS_OUT_OF_BOUNDS:          return "STATUS_OUT_OF_BOUNDS";
        case STATUS_INVALID_PARAMETER:      return "STATUS_INVALID_PARAMETER";
        case STATUS_INSUFFICIENT_RESOURCES: return "STATUS_INSUFFICIENT_RESOURCES";
        case STATUS_DENIED:                 return "STATUS_DENIED";
        default:                            return "STATUS_UNKNOWN_ERROR (Literally)";
    }
}

KERNEL_API STATUS GetLastError() {
    return lastStatus;
}

KERNEL_API void SetLastError(STATUS status) {
    lastStatus = status;
}