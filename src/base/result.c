/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/base/result.c
 *
 * PURPOSE:
 *   Implement explicit result values.
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

#include <stdio.h>
#include <string.h>
#include <umicom/platform/result.h>
UmiPlatformResult umi_platform_result_ok(void) {
    UmiPlatformResult result = { .code = UMI_PLATFORM_OK, .message = "ok" };
    return result;
}
UmiPlatformResult umi_platform_result_error(UmiPlatformResultCode code, const char *message) {
    UmiPlatformResult result = { .code = code, .message = "" };
    if (message != NULL) {
        (void)snprintf(result.message, sizeof(result.message), "%s", message);
    }
    return result;
}
bool umi_platform_result_is_ok(UmiPlatformResult result) { return result.code == UMI_PLATFORM_OK; }
