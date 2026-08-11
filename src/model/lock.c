/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/model/lock.c
 *
 * PURPOSE:
 *   Read the pinned root Framework revision.
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
#include <umicom/platform/json.h>
#include <umicom/platform/lock.h>
UmiPlatformResult umi_platform_lock_framework_sha(char *output, size_t capacity) {
    char json[16384];
    if (!umi_platform_read_text_file(UMI_PLATFORM_LOCK_FILE, json, sizeof(json), NULL)) return umi_platform_result_error(UMI_PLATFORM_ERROR_IO, "cannot read VERSION_LOCK.json");
    if (!umi_platform_json_get_string(json, "framework", output, capacity)) return umi_platform_result_error(UMI_PLATFORM_ERROR_PARSE, "framework SHA not found in lock");
    return umi_platform_result_ok();
}
