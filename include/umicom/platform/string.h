/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/string.h
 *
 * PURPOSE:
 *   Provide bounded string helpers so bootstrap code avoids unsafe unbounded copies.
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

#ifndef UMICOM_PLATFORM_STRING_H
#define UMICOM_PLATFORM_STRING_H
#include <stdbool.h>
#include <stddef.h>
bool umi_platform_string_copy(char *destination, size_t capacity, const char *source);
bool umi_platform_string_equal(const char *left, const char *right);
bool umi_platform_string_starts_with(const char *text, const char *prefix);
void umi_platform_string_trim(char *text);
#endif
