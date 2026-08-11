/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_integration_graph.c
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
#include <umicom/platform/workspace/integration_graph.h>
int main(void) {
    UMI_TEST_ASSERT(umi_platform_result_is_ok(
        umi_workspace_print_integration_graph()));
    return 0;
}
