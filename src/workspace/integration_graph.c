/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/integration_graph.c
 *
 * PURPOSE:
 *   Render required and optional suite relationships without private product dependencies.
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
#include <umicom/platform/workspace.h>
#include <umicom/platform/workspace/integration_graph.h>

UmiPlatformResult umi_workspace_print_integration_graph(void)
{
    UmiPlatformWorkspace workspace;
    UmiPlatformResult result = umi_platform_workspace_load(&workspace);
    size_t suite_index;

    if (!umi_platform_result_is_ok(result)) {
        return result;
    }

    puts("Umicom Integration Fabric suite graph");
    puts("Framework contracts / typed commands, events and queries");
    for (suite_index = 0U; suite_index < workspace.suite_count; ++suite_index) {
        const UmiPlatformSuite *suite = &workspace.suites[suite_index];
        size_t member_index;
        printf("\n%s [%s]\n", suite->id, suite->status);
        for (member_index = 0U;
             member_index < suite->required_member_count;
             ++member_index) {
            printf("  |-- REQUIRED --> %s\n",
                   suite->required_members[member_index]);
        }
        for (member_index = 0U;
             member_index < suite->optional_member_count;
             ++member_index) {
            printf("  `-- OPTIONAL --> %s\n",
                   suite->optional_members[member_index]);
        }
    }
    return umi_platform_result_ok();
}
