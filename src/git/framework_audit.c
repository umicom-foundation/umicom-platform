/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/git/framework_audit.c
 *
 * PURPOSE:
 *   Compare nested Framework revisions with the platform lock.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file is part of the bootstrap layer for the Umicom Platform workspace.
 * The code is intentionally small and explicit so a new developer can follow
 * how the platform discovers projects, validates files and reports problems.
 */

#include <stdio.h>
#include <string.h>
#include <umicom/platform/framework_audit.h>
#include <umicom/platform/git.h>
#include <umicom/platform/lock.h>
#include <umicom/platform/path.h>
UmiPlatformResult umi_platform_framework_audit(const UmiPlatformWorkspace *workspace, UmiFrameworkAuditSummary *summary) {
    if (workspace == NULL || summary == NULL) return umi_platform_result_error(UMI_PLATFORM_ERROR_ARGUMENT, "audit arguments are required");
    memset(summary, 0, sizeof(*summary));
    char root_sha[UMI_PLATFORM_SHA_MAX];
    UmiPlatformResult lock_result = umi_platform_lock_framework_sha(root_sha, sizeof(root_sha));
    if (!umi_platform_result_is_ok(lock_result)) return lock_result;
    for (size_t i = 0u; i < workspace->project_count; ++i) {
        const UmiPlatformProject *project = &workspace->projects[i];
        if (!project->enabled || !project->framework_required || project->path[0] == '\0') continue;
        char nested[UMI_PLATFORM_PATH_MAX];
        if (!umi_platform_path_join(nested, sizeof(nested), project->path, "framework")) continue;
        ++summary->checked;
        char sha[UMI_PLATFORM_SHA_MAX];
        if (!umi_platform_git_head(nested, sha, sizeof(sha))) {
            ++summary->not_initialized;
            continue;
        }
        if (strcmp(root_sha, sha) == 0) ++summary->matched;
        else ++summary->mismatched;
    }
    return umi_platform_result_ok();
}
