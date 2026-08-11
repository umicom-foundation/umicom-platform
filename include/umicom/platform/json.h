/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/json.h
 *
 * PURPOSE:
 *   Read bounded string and boolean values from controlled Umicom JSON manifest files.
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

#ifndef UMICOM_PLATFORM_JSON_H
#define UMICOM_PLATFORM_JSON_H
#include <stdbool.h>
#include <stddef.h>
#include <umicom/platform/types.h>
bool umi_platform_json_get_string(const char *json, const char *key, char *output, size_t capacity);
bool umi_platform_json_get_bool(const char *json, const char *key, bool *output);
bool umi_platform_json_get_string_array(
    const char *json,
    const char *key,
    char output[][UMI_PLATFORM_ID_MAX],
    size_t maximum_items,
    size_t *out_count);
#endif
