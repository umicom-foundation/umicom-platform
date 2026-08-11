/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_workspace.c
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
#include <umicom/platform/workspace.h>
int main(void){ UmiPlatformWorkspace w; UmiPlatformResult r=umi_platform_workspace_load(&w); UMI_TEST_ASSERT(umi_platform_result_is_ok(r)); UMI_TEST_ASSERT(w.project_count>=16u); UMI_TEST_ASSERT(w.suite_count==5u); return 0; }
