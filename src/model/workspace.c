/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/model/workspace.c
 *
 * PURPOSE:
 *   Load indexed platform projects and suites.
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
#include <umicom/platform/config.h>
#include <umicom/platform/manifest.h>
#include <umicom/platform/string.h>
#include <umicom/platform/suite.h>
#include <umicom/platform/workspace.h>
static UmiPlatformResult load_project_index(UmiPlatformWorkspace *workspace) {
    FILE *file = fopen(UMI_PLATFORM_PROJECT_INDEX, "r");
    if (file == NULL) return umi_platform_result_error(UMI_PLATFORM_ERROR_IO, "cannot open project index");
    char line[UMI_PLATFORM_PATH_MAX];
    while (fgets(line, sizeof(line), file) != NULL) {
        umi_platform_string_trim(line);
        if (line[0] == '\0' || line[0] == '#') continue;
        if (workspace->project_count >= UMI_PLATFORM_MAX_PROJECTS) { fclose(file); return umi_platform_result_error(UMI_PLATFORM_ERROR_VALIDATION, "too many projects"); }
        UmiPlatformResult r = umi_platform_manifest_load_project(line, &workspace->projects[workspace->project_count]);
        if (!umi_platform_result_is_ok(r)) { fclose(file); return r; }
        ++workspace->project_count;
    }
    fclose(file);
    return umi_platform_result_ok();
}
static UmiPlatformResult load_suite_index(UmiPlatformWorkspace *workspace) {
    FILE *file = fopen(UMI_PLATFORM_SUITE_INDEX, "r");
    if (file == NULL) return umi_platform_result_error(UMI_PLATFORM_ERROR_IO, "cannot open suite index");
    char line[UMI_PLATFORM_PATH_MAX];
    while (fgets(line, sizeof(line), file) != NULL) {
        umi_platform_string_trim(line);
        if (line[0] == '\0' || line[0] == '#') continue;
        if (workspace->suite_count >= UMI_PLATFORM_MAX_SUITES) { fclose(file); return umi_platform_result_error(UMI_PLATFORM_ERROR_VALIDATION, "too many suites"); }
        UmiPlatformResult r = umi_platform_suite_load(line, &workspace->suites[workspace->suite_count]);
        if (!umi_platform_result_is_ok(r)) { fclose(file); return r; }
        ++workspace->suite_count;
    }
    fclose(file);
    return umi_platform_result_ok();
}
UmiPlatformResult umi_platform_workspace_load(UmiPlatformWorkspace *workspace) {
    if (workspace == NULL) return umi_platform_result_error(UMI_PLATFORM_ERROR_ARGUMENT, "workspace is required");
    memset(workspace, 0, sizeof(*workspace));
    UmiPlatformResult r = load_project_index(workspace);
    if (!umi_platform_result_is_ok(r)) return r;
    return load_suite_index(workspace);
}
