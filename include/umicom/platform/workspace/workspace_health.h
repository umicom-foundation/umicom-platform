/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/workspace_health.h
 *
 * PURPOSE:
 *   Summarise submodule and manifest health for automation-friendly reporting.
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

#ifndef UMICOM_PLATFORM_WORKSPACE_HEALTH_H
#define UMICOM_PLATFORM_WORKSPACE_HEALTH_H
#include <stddef.h>
typedef struct UmiWorkspaceHealth {
    size_t active_projects;
    size_t planned_projects;
    size_t missing_active_paths;
    size_t submodules_initialized;
    size_t submodules_not_initialized;
    size_t submodules_different_commit;
} UmiWorkspaceHealth;
int umi_workspace_health_collect(UmiWorkspaceHealth *health);
#endif
