/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/plan.c
 *
 * PURPOSE:
 *   Implement plan-before-mutation workspace plans.
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

#include <stdio.h>
#include <string.h>
#include <umicom/platform/string.h>
#include <umicom/platform/workspace/plan.h>
void umi_workspace_plan_init(UmiWorkspacePlan *plan, const char *title) {
    if (plan == NULL) return;
    memset(plan, 0, sizeof(*plan));
    if (title != NULL) (void)umi_platform_string_copy(plan->title, sizeof(plan->title), title);
}
bool umi_workspace_plan_add(UmiWorkspacePlan *plan, const char *step) {
    if (plan == NULL || step == NULL || plan->step_count >= UMI_WORKSPACE_PLAN_MAX_STEPS) return false;
    if (!umi_platform_string_copy(plan->steps[plan->step_count], UMI_WORKSPACE_PLAN_STEP_MAX, step)) return false;
    ++plan->step_count;
    return true;
}
void umi_workspace_plan_print(const UmiWorkspacePlan *plan) {
    if (plan == NULL) return;
    printf("%s\n", plan->title);
    printf("mutates=%s network=%s steps=%zu\n", plan->mutates ? "true":"false", plan->network_required ? "true":"false", plan->step_count);
    for (size_t i=0u;i<plan->step_count;++i) printf("  %zu. %s\n", i+1u, plan->steps[i]);
}
