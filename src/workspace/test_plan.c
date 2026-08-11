/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/test_plan.c
 *
 * PURPOSE:
 *   Report the platform test order.
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

#include <stdio.h>
#include <umicom/platform/workspace.h>
#include <umicom/platform/workspace/test_plan.h>
UmiPlatformResult umi_workspace_print_test_plan(void){
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w);
    if(!umi_platform_result_is_ok(r)) return r;
    puts("Test plan:");
    for(size_t i=0u;i<w.project_count;++i) if(w.projects[i].enabled) printf("  unit/integration -> %s\n",w.projects[i].id);
    puts("  platform integration");
    puts("  Framework SHA convergence");
    puts("  CodeGuard cross-repository architecture");
    return umi_platform_result_ok();
}
