/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/plan.h
 *
 * PURPOSE:
 *   Store a bounded list of commands or explanations before any workspace mutation.
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

#ifndef UMICOM_PLATFORM_PLAN_H
#define UMICOM_PLATFORM_PLAN_H
#include <stdbool.h>
#include <stddef.h>
#define UMI_WORKSPACE_PLAN_MAX_STEPS 128u
#define UMI_WORKSPACE_PLAN_STEP_MAX 512u
typedef struct UmiWorkspacePlan {
    char title[128];
    char steps[UMI_WORKSPACE_PLAN_MAX_STEPS][UMI_WORKSPACE_PLAN_STEP_MAX];
    size_t step_count;
    bool mutates;
    bool network_required;
} UmiWorkspacePlan;
void umi_workspace_plan_init(UmiWorkspacePlan *plan, const char *title);
bool umi_workspace_plan_add(UmiWorkspacePlan *plan, const char *step);
void umi_workspace_plan_print(const UmiWorkspacePlan *plan);
#endif
