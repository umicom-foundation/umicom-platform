/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/sync.h
 *
 * PURPOSE:
 *   Plan and apply only safe pinned recursive Git submodule synchronisation.
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

#ifndef UMICOM_PLATFORM_SYNC_H
#define UMICOM_PLATFORM_SYNC_H
#include <umicom/platform/workspace/plan.h>
#include <umicom/platform/result.h>
UmiPlatformResult umi_workspace_sync_pinned_plan(UmiWorkspacePlan *plan);
UmiPlatformResult umi_workspace_sync_pinned_apply(void);
#endif
