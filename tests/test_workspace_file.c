/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_workspace_file.c
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
#include <umicom/platform/filesystem.h>
int main(void){ UMI_TEST_ASSERT(umi_platform_file_exists("umicom-workspace.json")); return 0; }
