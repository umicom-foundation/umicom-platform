/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_plan_overflow_guard.c
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
#include <umicom/platform/workspace/plan.h>
int main(void){UmiWorkspacePlan p;umi_workspace_plan_init(&p,"x");for(size_t i=0u;i<UMI_WORKSPACE_PLAN_MAX_STEPS;++i)UMI_TEST_ASSERT(umi_workspace_plan_add(&p,"x"));UMI_TEST_ASSERT(!umi_workspace_plan_add(&p,"overflow"));return 0;}
