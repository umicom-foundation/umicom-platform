/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/migration_plan.c
 *
 * PURPOSE:
 *   Report planned repository/layout migrations.
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
#include <string.h>
#include <umicom/platform/workspace.h>
#include <umicom/platform/workspace/migration_plan.h>
UmiPlatformResult umi_workspace_print_migration_plan(void){
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w);
    if(!umi_platform_result_is_ok(r)) return r;
    puts("Planned repository/layout migrations:");
    for(size_t i=0u;i<w.project_count;++i) if(strncmp(w.projects[i].status,"planned",7u)==0) printf("  %s -> %s\n",w.projects[i].id,w.projects[i].status);
    return umi_platform_result_ok();
}
