/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/suite_command.c
 *
 * PURPOSE:
 *   Implement native suite inspection and readiness planning without launching products yet.
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
#include <umicom/platform/suite_runtime.h>
#include <umicom/platform/filesystem.h>
#include <umicom/platform/workspace/suite_command.h>

static int load_workspace(UmiPlatformWorkspace *workspace)
{
    UmiPlatformResult result = umi_platform_workspace_load(workspace);
    if (!umi_platform_result_is_ok(result)) {
        fprintf(stderr, "%s\n", result.message);
        return 1;
    }
    return 0;
}

static void print_members(
    const char *label,
    const char members[][UMI_PLATFORM_ID_MAX],
    size_t count)
{
    size_t index;
    printf("%s (%zu):\n", label, count);
    for (index = 0U; index < count; ++index) {
        printf("  %s\n", members[index]);
    }
}

static int command_list(void)
{
    UmiPlatformWorkspace workspace;
    size_t index;
    if (load_workspace(&workspace) != 0) {
        return 1;
    }
    for (index = 0U; index < workspace.suite_count; ++index) {
        const UmiPlatformSuite *suite = &workspace.suites[index];
        printf("%-28s %-10s enabled=%s required=%zu optional=%zu\n",
               suite->id,
               suite->status,
               suite->enabled ? "yes" : "no",
               suite->required_member_count,
               suite->optional_member_count);
    }
    return 0;
}

static int command_show(const char *suite_id)
{
    UmiPlatformWorkspace workspace;
    const UmiPlatformSuite *suite;
    if (load_workspace(&workspace) != 0) {
        return 1;
    }
    suite = umi_platform_workspace_find_suite(&workspace, suite_id);
    if (suite == NULL) {
        fprintf(stderr, "suite not found: %s\n", suite_id);
        return 2;
    }
    printf("%s\n%s\nstatus=%s enabled=%s\n",
           suite->id,
           suite->name,
           suite->status,
           suite->enabled ? "yes" : "no");
    print_members("required", suite->required_members,
                  suite->required_member_count);
    print_members("optional", suite->optional_members,
                  suite->optional_member_count);
    return 0;
}

static int command_plan(const char *suite_id, bool validate_only)
{
    UmiPlatformWorkspace workspace;
    const UmiPlatformSuite *suite;
    UmiPlatformSuiteReadiness readiness;
    size_t index;
    UmiPlatformResult result;

    if (load_workspace(&workspace) != 0) {
        return 1;
    }
    suite = umi_platform_workspace_find_suite(&workspace, suite_id);
    if (suite == NULL) {
        fprintf(stderr, "suite not found: %s\n", suite_id);
        return 2;
    }

    result = umi_platform_suite_readiness(
        &workspace, suite, &readiness);
    if (!umi_platform_result_is_ok(result)) {
        fprintf(stderr, "%s\n", result.message);
        return 1;
    }

    printf("Suite: %s\n", suite->id);
    printf("Result: %s\n",
           readiness.ready
               ? (readiness.degraded ? "READY-DEGRADED" : "READY")
               : "BLOCKED");
    printf("Required: %zu/%zu available\n",
           readiness.required_available,
           readiness.required_total);
    printf("Optional: %zu/%zu available\n",
           readiness.optional_available,
           readiness.optional_total);

    if (!validate_only) {
        puts("Launch order / availability:");
        for (index = 0U; index < suite->required_member_count; ++index) {
            const UmiPlatformProject *project =
                umi_platform_workspace_find_project(
                    &workspace, suite->required_members[index]);
            printf("  REQUIRED %-30s %s\n",
                   suite->required_members[index],
                   project != NULL && project->enabled &&
                   project->path[0] != '\0' &&
                   umi_platform_path_exists(project->path)
                       ? "READY" : "MISSING");
        }
        for (index = 0U; index < suite->optional_member_count; ++index) {
            const UmiPlatformProject *project =
                umi_platform_workspace_find_project(
                    &workspace, suite->optional_members[index]);
            printf("  OPTIONAL %-30s %s\n",
                   suite->optional_members[index],
                   project != NULL && project->enabled &&
                   project->path[0] != '\0' &&
                   umi_platform_path_exists(project->path)
                       ? "READY" : "SKIP");
        }
    }

    return readiness.ready ? 0 : 2;
}

int umi_workspace_suite_command(int argc, char **argv)
{
    if (argc < 1) {
        puts("usage: workspace suite list|show|plan|validate [suite-id]");
        return 0;
    }
    if (strcmp(argv[0], "list") == 0) {
        return command_list();
    }
    if (argc < 2) {
        fputs("suite id is required\n", stderr);
        return 2;
    }
    if (strcmp(argv[0], "show") == 0) {
        return command_show(argv[1]);
    }
    if (strcmp(argv[0], "plan") == 0) {
        return command_plan(argv[1], false);
    }
    if (strcmp(argv[0], "validate") == 0) {
        return command_plan(argv[1], true);
    }
    fprintf(stderr, "unknown suite command: %s\n", argv[0]);
    return 2;
}
