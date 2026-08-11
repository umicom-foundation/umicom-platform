/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_suite_policy_files.c
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
#include <umicom/platform/filesystem.h>
int main(void) {
    UMI_TEST_ASSERT(umi_platform_file_exists("manifests/policies/optional-application-independence.json"));
    UMI_TEST_ASSERT(umi_platform_file_exists("manifests/policies/inter-application-public-contracts.json"));
    return 0;
}
