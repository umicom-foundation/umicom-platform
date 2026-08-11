/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/validation/project_validator.c
 *
 * PURPOSE:
 *   Validate project manifest fields.
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
#include <umicom/platform/path.h>
#include <umicom/platform/project.h>
bool umi_platform_validation_project_fields(const UmiPlatformProject *project) {
    return project != NULL && project->id[0] != '\0' && project->name[0] != '\0' &&
           project->status[0] != '\0' && umi_platform_path_is_safe_relative(project->path);
}
