/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/model/manifest.c
 *
 * PURPOSE:
 *   Load project manifest metadata.
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

#include <string.h>
#include <umicom/platform/filesystem.h>
#include <umicom/platform/json.h>
#include <umicom/platform/manifest.h>
UmiPlatformResult umi_platform_manifest_load_project(const char *path, UmiPlatformProject *project) {
    if (path == NULL || project == NULL) return umi_platform_result_error(UMI_PLATFORM_ERROR_ARGUMENT, "manifest arguments are required");
    char json[8192];
    if (!umi_platform_read_text_file(path, json, sizeof(json), NULL)) return umi_platform_result_error(UMI_PLATFORM_ERROR_IO, "cannot read project manifest");
    memset(project, 0, sizeof(*project));
    if (!umi_platform_json_get_string(json, "id", project->id, sizeof(project->id))) return umi_platform_result_error(UMI_PLATFORM_ERROR_PARSE, "project id missing");
    if (!umi_platform_json_get_string(json, "name", project->name, sizeof(project->name))) return umi_platform_result_error(UMI_PLATFORM_ERROR_PARSE, "project name missing");
    if (!umi_platform_json_get_string(json, "type", project->type, sizeof(project->type))) return umi_platform_result_error(UMI_PLATFORM_ERROR_PARSE, "project type missing");
    if (!umi_platform_json_get_string(json, "path", project->path, sizeof(project->path))) return umi_platform_result_error(UMI_PLATFORM_ERROR_PARSE, "project path missing");
    (void)umi_platform_json_get_string(json, "repository", project->repository, sizeof(project->repository));
    if (!umi_platform_json_get_string(json, "status", project->status, sizeof(project->status))) return umi_platform_result_error(UMI_PLATFORM_ERROR_PARSE, "project status missing");
    (void)umi_platform_json_get_bool(json, "enabled", &project->enabled);
    (void)umi_platform_json_get_bool(json, "framework_required", &project->framework_required);
    return umi_platform_result_ok();
}
