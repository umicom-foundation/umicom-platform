/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/operation.h
 *
 * PURPOSE:
 *   Describe whether a workspace operation is read-only or mutating.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file implements one small part of the native Umicom Platform workspace
 * orchestrator. The logic stays explicit so new developers can follow how the
 * super-project plans and validates recursive Git, build and release actions.
 */

#ifndef UMICOM_PLATFORM_OPERATION_H
#define UMICOM_PLATFORM_OPERATION_H
#include <stdbool.h>
#include <stddef.h>
typedef enum UmiWorkspaceOperationKind {
    UMI_WORKSPACE_OPERATION_READ_ONLY = 0,
    UMI_WORKSPACE_OPERATION_MUTATING = 1
} UmiWorkspaceOperationKind;
typedef struct UmiWorkspaceOperation {
    char id[64];
    char description[192];
    UmiWorkspaceOperationKind kind;
    bool network_required;
} UmiWorkspaceOperation;
#endif
