/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/workspace_command.c
 *
 * PURPOSE:
 *   Dispatch native workspace orchestration commands.
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
#include <umicom/platform/framework_audit.h>
#include <umicom/platform/reporter.h>
#include <umicom/platform/workspace.h>
#include <umicom/platform/workspace/build_plan.h>
#include <umicom/platform/workspace/codeguard_plan.h>
#include <umicom/platform/workspace/graph.h>
#include <umicom/platform/workspace/lock_plan.h>
#include <umicom/platform/workspace/migration_plan.h>
#include <umicom/platform/workspace/os_ui.h>
#include <umicom/platform/workspace/remote_plan.h>
#include <umicom/platform/workspace/sync.h>
#include <umicom/platform/workspace/test_plan.h>
#include <umicom/platform/workspace/workspace_status.h>
#include <umicom/platform/workspace/workspace_command.h>
static int print_result(UmiPlatformResult r){if(!umi_platform_result_is_ok(r)){fprintf(stderr,"%s\n",r.message);return 1;}return 0;}
static int audit(void){
    UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w); if(!umi_platform_result_is_ok(r)) return print_result(r);
    UmiFrameworkAuditSummary s; r=umi_platform_framework_audit(&w,&s); if(!umi_platform_result_is_ok(r)) return print_result(r);
    umi_platform_report_framework_audit(&s); return s.mismatched==0u?0:2;
}
int umi_platform_workspace_command(int argc,char **argv){
    if(argc<1){puts("workspace commands: status graph sync framework-audit lock-plan build-plan test-plan codeguard-plan os-ui remote-plan migration-plan");return 0;}
    const char *cmd=argv[0];
    if(strcmp(cmd,"status")==0) return print_result(umi_workspace_print_status());
    if(strcmp(cmd,"graph")==0) return print_result(umi_workspace_print_graph());
    if(strcmp(cmd,"framework-audit")==0) return audit();
    if(strcmp(cmd,"lock-plan")==0) return print_result(umi_workspace_print_lock_plan());
    if(strcmp(cmd,"build-plan")==0) return print_result(umi_workspace_print_build_plan());
    if(strcmp(cmd,"test-plan")==0) return print_result(umi_workspace_print_test_plan());
    if(strcmp(cmd,"codeguard-plan")==0) return print_result(umi_workspace_print_codeguard_plan());
    if(strcmp(cmd,"os-ui")==0){umi_workspace_print_os_ui_policy();return 0;}
    if(strcmp(cmd,"remote-plan")==0) return print_result(umi_workspace_print_remote_plan());
    if(strcmp(cmd,"migration-plan")==0) return print_result(umi_workspace_print_migration_plan());
    if(strcmp(cmd,"sync")==0){
        if(argc<3 || strcmp(argv[1],"--pinned")!=0){fputs("usage: workspace sync --pinned --plan|--apply\n",stderr);return 2;}
        if(strcmp(argv[2],"--plan")==0){UmiWorkspacePlan p; UmiPlatformResult r=umi_workspace_sync_pinned_plan(&p); if(!umi_platform_result_is_ok(r))return print_result(r); umi_workspace_plan_print(&p);return 0;}
        if(strcmp(argv[2],"--apply")==0) return print_result(umi_workspace_sync_pinned_apply());
        fputs("usage: workspace sync --pinned --plan|--apply\n",stderr); return 2;
    }
    fprintf(stderr,"unknown workspace command: %s\n",cmd); return 2;
}
