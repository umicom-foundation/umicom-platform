/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_suite_optional_missing.c
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

#include <string.h>
#include <stdio.h>
#include <umi_test.h>
#include <umicom/platform/suite_runtime.h>
int main(void) {
    UmiPlatformWorkspace w={0}; UmiPlatformSuiteReadiness r;
    w.project_count=1U;
    (void)snprintf(w.projects[0].id,sizeof(w.projects[0].id),"required");
    (void)snprintf(w.projects[0].path,sizeof(w.projects[0].path),".");
    w.projects[0].enabled=true;
    w.suite_count=1U; w.suites[0].enabled=true;
    (void)snprintf(w.suites[0].id,sizeof(w.suites[0].id),"suite");
    (void)snprintf(w.suites[0].required_members[0],UMI_PLATFORM_ID_MAX,"required");
    (void)snprintf(w.suites[0].optional_members[0],UMI_PLATFORM_ID_MAX,"future");
    w.suites[0].required_member_count=1U; w.suites[0].optional_member_count=1U;
    UMI_TEST_ASSERT(umi_platform_result_is_ok(
        umi_platform_suite_readiness(&w,&w.suites[0],&r)));
    UMI_TEST_ASSERT(r.ready && r.degraded);
    UMI_TEST_ASSERT(r.required_missing==0U && r.optional_missing==1U);
    return 0;
}
