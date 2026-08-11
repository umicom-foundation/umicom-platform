/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/workspace_policy.h
 *
 * PURPOSE:
 *   Expose fixed safety rules for native workspace operations.
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

#ifndef UMICOM_PLATFORM_WORKSPACE_POLICY_H
#define UMICOM_PLATFORM_WORKSPACE_POLICY_H
#include <stdbool.h>
bool umi_workspace_policy_allows_auto_push(void);
bool umi_workspace_policy_requires_remote_plan(void);
bool umi_workspace_policy_pinned_sync_allowed(void);
#endif
