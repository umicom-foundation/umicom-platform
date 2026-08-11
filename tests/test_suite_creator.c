/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_suite_creator.c
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

#include <umi_test.h>
#include <umicom/platform/suite.h>
int main(void) {
    UmiPlatformSuite s;
    UMI_TEST_ASSERT(umi_platform_result_is_ok(
        umi_platform_suite_load("manifests/suites/creator.json",&s)));
    UMI_TEST_ASSERT(s.enabled && s.required_member_count==1U);
    return 0;
}
