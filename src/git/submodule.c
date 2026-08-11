/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/git/submodule.c
 *
 * PURPOSE:
 *   Check whether a submodule working tree is initialised.
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

#include <umicom/platform/types.h>
#include <umicom/platform/filesystem.h>
#include <umicom/platform/path.h>
#include <umicom/platform/submodule.h>
bool umi_platform_submodule_initialized(const char *path) {
    char dotgit[UMI_PLATFORM_PATH_MAX];
    if (!umi_platform_path_join(dotgit, sizeof(dotgit), path, ".git")) return false;
    return umi_platform_path_exists(dotgit);
}
