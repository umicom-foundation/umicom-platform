/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/codeguard_plan.c
 *
 * PURPOSE:
 *   Report cross-repository CodeGuard scan roots.
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
#include <umicom/platform/workspace/codeguard_plan.h>
UmiPlatformResult umi_workspace_print_codeguard_plan(void){
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w);
    if(!umi_platform_result_is_ok(r)) return r;
    puts("CodeGuard workspace roots:");
    puts("  framework");
    for(size_t i=0u;i<w.project_count;++i) if(w.projects[i].enabled && w.projects[i].path[0]!='\0') printf("  %s\n",w.projects[i].path);
    puts("Cross-repository checks: duplicate implementations, private Framework headers, database authority, frontend boundary, Framework SHA drift.");
    return umi_platform_result_ok();
}
