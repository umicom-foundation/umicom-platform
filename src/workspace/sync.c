/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/sync.c
 *
 * PURPOSE:
 *   Plan and apply pinned recursive submodule synchronisation.
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

#include <umicom/platform/workspace/git_command.h>
#include <umicom/platform/workspace/sync.h>
UmiPlatformResult umi_workspace_sync_pinned_plan(UmiWorkspacePlan *plan) {
    if(plan==NULL) return umi_platform_result_error(UMI_PLATFORM_ERROR_ARGUMENT,"plan required");
    umi_workspace_plan_init(plan,"Pinned recursive submodule sync");
    plan->mutates=true;
    plan->network_required=true;
    (void)umi_workspace_plan_add(plan,"git submodule sync --recursive");
    (void)umi_workspace_plan_add(plan,"git submodule update --init --recursive");
    (void)umi_workspace_plan_add(plan,"git submodule status --recursive");
    return umi_platform_result_ok();
}
UmiPlatformResult umi_workspace_sync_pinned_apply(void) {
    int code=-1;
    if(!umi_git_command_run("submodule sync --recursive",&code) || code!=0) return umi_platform_result_error(UMI_PLATFORM_ERROR_PROCESS,"git submodule sync failed");
    if(!umi_git_command_run("submodule update --init --recursive",&code) || code!=0) return umi_platform_result_error(UMI_PLATFORM_ERROR_PROCESS,"git submodule update failed");
    return umi_platform_result_ok();
}
