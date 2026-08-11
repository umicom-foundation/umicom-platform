/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/commands/cmd_lock.c
 *
 * PURPOSE:
 *   Implement one native Umicom Platform bootstrap command.
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
#include <umicom/platform/lock.h>
int umi_cmd_lock(void) {
    char sha[UMI_PLATFORM_SHA_MAX];
    UmiPlatformResult r = umi_platform_lock_framework_sha(sha, sizeof(sha));
    if (!umi_platform_result_is_ok(r)) { fprintf(stderr, "%s\n", r.message); return 1; }
    printf("framework=%s\n", sha);
    return 0;
}
