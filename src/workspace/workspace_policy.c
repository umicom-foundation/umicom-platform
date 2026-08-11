/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/workspace_policy.c
 *
 * PURPOSE:
 *   Encode workspace mutation safety defaults.
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

#include <umicom/platform/workspace/workspace_policy.h>
bool umi_workspace_policy_allows_auto_push(void){return false;}
bool umi_workspace_policy_requires_remote_plan(void){return true;}
bool umi_workspace_policy_pinned_sync_allowed(void){return true;}
