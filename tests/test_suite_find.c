/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_suite_find.c
 *
 * PURPOSE:
 *   Exercise one Batch 18 suite or Integration Fabric orchestration behaviour.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file keeps suite and integration orchestration explicit. The master
 * platform plans composition, but products remain independent repositories
 * communicating through Framework contracts rather than private state.
 */

#include <stdio.h>
#include <string.h>
#include <umi_test.h>
#include <umicom/platform/suite_runtime.h>
int main(void) {
    UmiPlatformWorkspace w={0};
    w.project_count=1U; w.suite_count=1U;
    (void)snprintf(w.projects[0].id,sizeof(w.projects[0].id),"project");
    (void)snprintf(w.suites[0].id,sizeof(w.suites[0].id),"suite");
    UMI_TEST_ASSERT(umi_platform_workspace_find_project(&w,"project")!=NULL);
    UMI_TEST_ASSERT(umi_platform_workspace_find_suite(&w,"suite")!=NULL);
    UMI_TEST_ASSERT(umi_platform_workspace_find_suite(&w,"missing")==NULL);
    return 0;
}
