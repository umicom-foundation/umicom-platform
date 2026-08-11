/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/validation/path_validator.c
 *
 * PURPOSE:
 *   Validate enabled project paths.
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

#include <umicom/platform/filesystem.h>
#include <umicom/platform/project.h>
bool umi_platform_validation_project_path(const UmiPlatformProject *project) {
    if (!umi_platform_project_requires_path(project)) return true;
    return umi_platform_path_exists(project->path);
}
