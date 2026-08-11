/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/model/project.c
 *
 * PURPOSE:
 *   Classify current and planned projects.
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

#include <umicom/platform/project.h>
#include <umicom/platform/string.h>
bool umi_platform_project_is_planned(const UmiPlatformProject *project) {
    return project != NULL && (umi_platform_string_starts_with(project->status, "planned") || umi_platform_string_equal(project->status, "planned-migration"));
}
bool umi_platform_project_requires_path(const UmiPlatformProject *project) {
    return project != NULL && project->enabled && !umi_platform_project_is_planned(project);
}
