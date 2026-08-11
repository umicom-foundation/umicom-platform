/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/git.h
 *
 * PURPOSE:
 *   Provide read-only Git helpers for repository and submodule inspection.
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

#ifndef UMICOM_PLATFORM_GIT_H
#define UMICOM_PLATFORM_GIT_H
#include <stdbool.h>
#include <stddef.h>
bool umi_platform_git_available(void);
bool umi_platform_git_head(const char *path, char *sha, size_t capacity);
#endif
