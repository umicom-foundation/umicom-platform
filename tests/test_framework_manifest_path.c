/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_framework_manifest_path.c
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
#include <umicom/platform/manifest.h>
#include <umicom/platform/path.h>
int main(void){ UmiPlatformProject p; UMI_TEST_ASSERT(umi_platform_result_is_ok(umi_platform_manifest_load_project("manifests/projects/framework.json",&p))); UMI_TEST_ASSERT(umi_platform_path_is_safe_relative(p.path)); return 0; }
