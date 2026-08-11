/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/platform/toolchain.c
 *
 * PURPOSE:
 *   Probe required bootstrap tools.
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

#include <umicom/platform/process.h>
#include <umicom/platform/toolchain.h>
static bool command_ok(const char *command) {
    char output[256];
    int code = -1;
    return umi_platform_process_capture(command, output, sizeof(output), &code) && code == 0;
}
UmiPlatformToolchainStatus umi_platform_toolchain_probe(void) {
    UmiPlatformToolchainStatus status = {
        .git = command_ok("git --version 2>&1"),
        .cmake = command_ok("cmake --version 2>&1"),
        .ninja = command_ok("ninja --version 2>&1")
    };
    return status;
}
