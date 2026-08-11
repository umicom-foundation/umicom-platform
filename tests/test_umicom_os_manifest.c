/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_umicom_os_manifest.c
 *
 * PURPOSE:
 *   Exercise one Batch 16 workspace orchestration or OS/UI architecture behaviour.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file implements one small part of the native Umicom Platform workspace
 * orchestrator. The logic stays explicit so new developers can follow how the
 * super-project plans and validates recursive Git, build and release actions.
 */
#include <umi_test.h>
#include <umicom/platform/manifest.h>
int main(void){UmiPlatformProject p;UMI_TEST_ASSERT(umi_platform_result_is_ok(umi_platform_manifest_load_project("manifests/projects/umicom-os.json",&p)));UMI_TEST_ASSERT(p.framework_required);return 0;}
