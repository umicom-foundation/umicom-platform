/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/filesystem.h
 *
 * PURPOSE:
 *   Expose small portable file and directory checks used during workspace validation.
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

#ifndef UMICOM_PLATFORM_FILESYSTEM_H
#define UMICOM_PLATFORM_FILESYSTEM_H
#include <stdbool.h>
#include <stddef.h>
bool umi_platform_path_exists(const char *path);
bool umi_platform_file_exists(const char *path);
bool umi_platform_directory_exists(const char *path);
bool umi_platform_read_text_file(const char *path, char *buffer, size_t capacity, size_t *out_length);
#endif
