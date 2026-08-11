/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/commands/cmd_doctor.c
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
#include <umicom/platform/toolchain.h>
int umi_cmd_doctor(void) {
    UmiPlatformToolchainStatus s = umi_platform_toolchain_probe();
    printf("git   : %s\n", s.git ? "OK" : "MISSING");
    printf("cmake : %s\n", s.cmake ? "OK" : "MISSING");
    printf("ninja : %s\n", s.ninja ? "OK" : "MISSING");
    return (s.git && s.cmake && s.ninja) ? 0 : 1;
}
