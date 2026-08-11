/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/status.c
 *
 * PURPOSE:
 *   Report manifest and recursive submodule status.
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
#include <umicom/platform/workspace/submodule_status.h>
#include <umicom/platform/workspace/workspace_status.h>
UmiPlatformResult umi_workspace_print_status(void){
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w);
    if(!umi_platform_result_is_ok(r)) return r;
    puts("Projects:");
    for(size_t i=0u;i<w.project_count;++i){
        UmiProjectState s; (void)umi_project_state_read(&w.projects[i],&s);
        printf("  %-30s %-18s path=%s head=%s\n",s.project.id,s.project.status,s.path_exists?"yes":"no",s.head_available?s.head:"-");
    }
    UmiSubmoduleSnapshot snap;
    if(umi_submodule_status_snapshot(&snap)){
        puts("Recursive submodules:");
        for(size_t i=0u;i<snap.count;++i) printf("  %-56s %s\n",snap.records[i].path,umi_submodule_state_name(snap.records[i].state));
    }
    return umi_platform_result_ok();
}
