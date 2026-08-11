/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_path_safe.c
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
#include <umicom/platform/path.h>
int main(void){ UMI_TEST_ASSERT(umi_platform_path_is_safe_relative("applications/tms")); UMI_TEST_ASSERT(!umi_platform_path_is_safe_relative("../secret")); UMI_TEST_ASSERT(!umi_platform_path_is_safe_relative("/absolute")); return 0; }
