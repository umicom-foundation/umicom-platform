/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/validation/lock_validator.c
 *
 * PURPOSE:
 *   Validate the locked Framework SHA.
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
#include <umicom/platform/lock.h>
bool umi_platform_validation_lock_sha(void) {
    char sha[UMI_PLATFORM_SHA_MAX];
    UmiPlatformResult result = umi_platform_lock_framework_sha(sha, sizeof(sha));
    return umi_platform_result_is_ok(result) && strlen(sha) == 40u;
}
