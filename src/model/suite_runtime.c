/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/model/suite_runtime.c
 *
 * PURPOSE:
 *   Implement suite readiness while allowing unavailable optional products.
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
#include <umicom/platform/filesystem.h>
#include <umicom/platform/suite_runtime.h>

const UmiPlatformProject *umi_platform_workspace_find_project(
    const UmiPlatformWorkspace *workspace,
    const char *project_id)
{
    size_t index;
    if (workspace == NULL || project_id == NULL) {
        return NULL;
    }
    for (index = 0U; index < workspace->project_count; ++index) {
        if (strcmp(workspace->projects[index].id, project_id) == 0) {
            return &workspace->projects[index];
        }
    }
    return NULL;
}

const UmiPlatformSuite *umi_platform_workspace_find_suite(
    const UmiPlatformWorkspace *workspace,
    const char *suite_id)
{
    size_t index;
    if (workspace == NULL || suite_id == NULL) {
        return NULL;
    }
    for (index = 0U; index < workspace->suite_count; ++index) {
        if (strcmp(workspace->suites[index].id, suite_id) == 0) {
            return &workspace->suites[index];
        }
    }
    return NULL;
}

static bool project_available(
    const UmiPlatformWorkspace *workspace,
    const char *project_id)
{
    const UmiPlatformProject *project =
        umi_platform_workspace_find_project(workspace, project_id);
    return project != NULL &&
           project->enabled &&
           project->path[0] != '\0' &&
           umi_platform_path_exists(project->path);
}

UmiPlatformResult umi_platform_suite_readiness(
    const UmiPlatformWorkspace *workspace,
    const UmiPlatformSuite *suite,
    UmiPlatformSuiteReadiness *out_readiness)
{
    size_t index;

    if (workspace == NULL || suite == NULL || out_readiness == NULL) {
        return umi_platform_result_error(
            UMI_PLATFORM_ERROR_ARGUMENT,
            "suite readiness arguments are required");
    }

    (void)memset(out_readiness, 0, sizeof(*out_readiness));
    out_readiness->required_total = suite->required_member_count;
    out_readiness->optional_total = suite->optional_member_count;

    for (index = 0U; index < suite->required_member_count; ++index) {
        if (project_available(workspace, suite->required_members[index])) {
            ++out_readiness->required_available;
        } else {
            ++out_readiness->required_missing;
        }
    }
    for (index = 0U; index < suite->optional_member_count; ++index) {
        if (project_available(workspace, suite->optional_members[index])) {
            ++out_readiness->optional_available;
        } else {
            ++out_readiness->optional_missing;
        }
    }

    out_readiness->ready =
        suite->enabled && out_readiness->required_missing == 0U;
    out_readiness->degraded =
        out_readiness->ready && out_readiness->optional_missing > 0U;

    return umi_platform_result_ok();
}
