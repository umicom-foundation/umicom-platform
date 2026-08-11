/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/workspace_health.c
 *
 * PURPOSE:
 *   Collect basic platform health counters.
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

#include <string.h>
#include <umicom/platform/project.h>
#include <umicom/platform/workspace.h>
#include <umicom/platform/workspace/submodule_status.h>
#include <umicom/platform/workspace/workspace_health.h>
int umi_workspace_health_collect(UmiWorkspaceHealth *h){
    if(h==NULL) return 1;
    memset(h,0,sizeof(*h));
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w); if(!umi_platform_result_is_ok(r)) return 2;
    for(size_t i=0u;i<w.project_count;++i){
        if(w.projects[i].enabled) ++h->active_projects; else ++h->planned_projects;
    }
    UmiSubmoduleSnapshot s; if(umi_submodule_status_snapshot(&s)){
        for(size_t i=0u;i<s.count;++i){
            if(s.records[i].state==UMI_SUBMODULE_INITIALIZED) ++h->submodules_initialized;
            else if(s.records[i].state==UMI_SUBMODULE_NOT_INITIALIZED) ++h->submodules_not_initialized;
            else if(s.records[i].state==UMI_SUBMODULE_DIFFERENT_COMMIT) ++h->submodules_different_commit;
        }
    }
    return 0;
}
