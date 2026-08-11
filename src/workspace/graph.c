/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/graph.c
 *
 * PURPOSE:
 *   Report the Framework-centred project dependency graph.
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
#include <umicom/platform/workspace/graph.h>
UmiPlatformResult umi_workspace_print_graph(void){
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w);
    if(!umi_platform_result_is_ok(r)) return r;
    puts("Umicom Framework");
    for(size_t i=0u;i<w.project_count;++i){
        const UmiPlatformProject *p=&w.projects[i];
        if(p->framework_required) printf("  |--> %s [%s]\n",p->id,p->status);
    }
    puts("Optional application-to-application integration is routed through Framework capabilities / Integration Fabric.");
    return umi_platform_result_ok();
}
