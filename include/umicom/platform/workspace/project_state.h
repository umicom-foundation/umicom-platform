/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/project_state.h
 *
 * PURPOSE:
 *   Represent one project's enabled/planned/local state for reporting.
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

#ifndef UMICOM_PLATFORM_PROJECT_STATE_H
#define UMICOM_PLATFORM_PROJECT_STATE_H
#include <stdbool.h>
#include <umicom/platform/types.h>
typedef struct UmiProjectState {
    UmiPlatformProject project;
    bool path_exists;
    bool git_repository;
    bool head_available;
    char head[UMI_PLATFORM_SHA_MAX];
} UmiProjectState;
bool umi_project_state_read(const UmiPlatformProject *project, UmiProjectState *state);
#endif
