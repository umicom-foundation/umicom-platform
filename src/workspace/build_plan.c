/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/build_plan.c
 *
 * PURPOSE:
 *   Report a safe project build order.
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
#include <umicom/platform/workspace/build_plan.h>
static int priority(const UmiPlatformProject *p){
    if(strcmp(p->type,"framework")==0) return 0;
    if(strcmp(p->type,"service")==0) return 1;
    if(strcmp(p->type,"application")==0) return 2;
    if(strcmp(p->type,"operating-system")==0) return 3;
    return 4;
}
UmiPlatformResult umi_workspace_print_build_plan(void){
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w);
    if(!umi_platform_result_is_ok(r)) return r;
    puts("Build plan (execution begins in a later batch after per-repository presets are audited):");
    for(int pr=0;pr<=4;++pr) for(size_t i=0u;i<w.project_count;++i) if(w.projects[i].enabled&&priority(&w.projects[i])==pr) printf("  %s -> %s\n",w.projects[i].id,w.projects[i].path);
    return umi_platform_result_ok();
}
