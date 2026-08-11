/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/toolchain.h
 *
 * PURPOSE:
 *   Probe bootstrap build tools without changing the user's PATH or environment.
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

#ifndef UMICOM_PLATFORM_TOOLCHAIN_H
#define UMICOM_PLATFORM_TOOLCHAIN_H
#include <stdbool.h>
typedef struct UmiPlatformToolchainStatus {
    bool git;
    bool cmake;
    bool ninja;
} UmiPlatformToolchainStatus;
UmiPlatformToolchainStatus umi_platform_toolchain_probe(void);
#endif
