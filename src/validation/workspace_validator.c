/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/validation/workspace_validator.c
 *
 * PURPOSE:
 *   Validate required platform root files.
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

#include <umicom/platform/config.h>
#include <umicom/platform/filesystem.h>
bool umi_platform_validation_root_files(void) {
    return umi_platform_file_exists(UMI_PLATFORM_WORKSPACE_FILE) &&
           umi_platform_file_exists(UMI_PLATFORM_LOCK_FILE) &&
           umi_platform_file_exists(UMI_PLATFORM_PROJECT_INDEX) &&
           umi_platform_file_exists(UMI_PLATFORM_SUITE_INDEX);
}
