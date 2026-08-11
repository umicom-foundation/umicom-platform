/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_validator.c
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
#include <umicom/platform/validator.h>
int main(void){ UmiPlatformWorkspace w; UMI_TEST_ASSERT(umi_platform_result_is_ok(umi_platform_workspace_load(&w))); UmiPlatformValidationSummary s; UmiPlatformResult r=umi_platform_validate(&w,&s); UMI_TEST_ASSERT(umi_platform_result_is_ok(r)); UMI_TEST_ASSERT(s.failed==0u); return 0; }
