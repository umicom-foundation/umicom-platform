/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/path.h
 *
 * PURPOSE:
 *   Build repository-relative paths without unsafe concatenation.
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

#ifndef UMICOM_PLATFORM_PATH_H
#define UMICOM_PLATFORM_PATH_H
#include <stdbool.h>
#include <stddef.h>
bool umi_platform_path_join(char *output, size_t capacity, const char *left, const char *right);
bool umi_platform_path_is_safe_relative(const char *path);
#endif
