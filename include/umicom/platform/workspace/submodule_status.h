/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/submodule_status.h
 *
 * PURPOSE:
 *   Parse `git submodule status --recursive` into explicit local state.
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

#ifndef UMICOM_PLATFORM_SUBMODULE_STATUS_H
#define UMICOM_PLATFORM_SUBMODULE_STATUS_H
#include <stdbool.h>
#include <stddef.h>
#include <umicom/platform/types.h>
#define UMI_WORKSPACE_MAX_SUBMODULES 256u
typedef enum UmiSubmoduleState {
    UMI_SUBMODULE_INITIALIZED,
    UMI_SUBMODULE_NOT_INITIALIZED,
    UMI_SUBMODULE_DIFFERENT_COMMIT,
    UMI_SUBMODULE_CONFLICT
} UmiSubmoduleState;
typedef struct UmiSubmoduleRecord {
    char path[UMI_PLATFORM_PATH_MAX];
    char sha[UMI_PLATFORM_SHA_MAX];
    UmiSubmoduleState state;
} UmiSubmoduleRecord;
typedef struct UmiSubmoduleSnapshot {
    UmiSubmoduleRecord records[UMI_WORKSPACE_MAX_SUBMODULES];
    size_t count;
} UmiSubmoduleSnapshot;
bool umi_submodule_status_parse_line(const char *line, UmiSubmoduleRecord *record);
bool umi_submodule_status_snapshot(UmiSubmoduleSnapshot *snapshot);
const char *umi_submodule_state_name(UmiSubmoduleState state);
#endif
