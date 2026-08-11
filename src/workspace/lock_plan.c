/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/lock_plan.c
 *
 * PURPOSE:
 *   Report current project revisions without rewriting the lock.
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
#include <umicom/platform/project.h>
#include <umicom/platform/workspace.h>
#include <umicom/platform/workspace/project_state.h>
#include <umicom/platform/workspace/lock_plan.h>
UmiPlatformResult umi_workspace_print_lock_plan(void){
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w);
    if(!umi_platform_result_is_ok(r)) return r;
    puts("VERSION_LOCK next-state plan (read-only):");
    for(size_t i=0u;i<w.project_count;++i){
        const UmiPlatformProject *p=&w.projects[i];
        if(!p->enabled) continue;
        UmiProjectState s; (void)umi_project_state_read(p,&s);
        printf("  %-30s %s\n",p->id,s.head_available?s.head:"HEAD unavailable");
    }
    puts("No lock file was changed.");
    return umi_platform_result_ok();
}
