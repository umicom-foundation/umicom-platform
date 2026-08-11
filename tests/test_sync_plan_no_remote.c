/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_sync_plan_no_remote.c
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
#include <string.h>
#include <umi_test.h>
#include <umicom/platform/workspace/sync.h>
int main(void){UmiWorkspacePlan p;UMI_TEST_ASSERT(umi_platform_result_is_ok(umi_workspace_sync_pinned_plan(&p)));UMI_TEST_ASSERT(strstr(p.steps[1],"--remote")==NULL);return 0;}
