/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_manifest_framework.c
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
int main(void){ UmiPlatformProject p; UmiPlatformResult r=umi_platform_manifest_load_project("manifests/projects/framework.json",&p); UMI_TEST_ASSERT(umi_platform_result_is_ok(r)); UMI_TEST_ASSERT(p.enabled); return 0; }
