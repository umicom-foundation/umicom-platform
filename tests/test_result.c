/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_result.c
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
#include <umicom/platform/result.h>
int main(void){ UMI_TEST_ASSERT(umi_platform_result_is_ok(umi_platform_result_ok())); UMI_TEST_ASSERT(!umi_platform_result_is_ok(umi_platform_result_error(UMI_PLATFORM_ERROR_IO,"x"))); return 0; }
