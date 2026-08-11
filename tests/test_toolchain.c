/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_toolchain.c
 *
 * PURPOSE:
 *   Exercise one bounded platform bootstrap behaviour.
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
#include <umi_test.h>
#include <umicom/platform/toolchain.h>
int main(void){ UmiPlatformToolchainStatus s=umi_platform_toolchain_probe(); UMI_TEST_ASSERT(s.git); UMI_TEST_ASSERT(s.cmake); UMI_TEST_ASSERT(s.ninja); return 0; }
