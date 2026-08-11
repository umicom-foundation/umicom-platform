/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_suite.c
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
#include <umicom/platform/suite.h>
int main(void){ UmiPlatformSuite s; UmiPlatformResult r=umi_platform_suite_load("manifests/suites/studio.json",&s); UMI_TEST_ASSERT(umi_platform_result_is_ok(r)); return 0; }
