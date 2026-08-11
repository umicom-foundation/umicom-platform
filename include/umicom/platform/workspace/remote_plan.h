/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/remote_plan.h
 *
 * PURPOSE:
 *   Reserve a read-only remote advancement plan without applying changes in Stage 2.
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

#ifndef UMICOM_PLATFORM_REMOTE_PLAN_H
#define UMICOM_PLATFORM_REMOTE_PLAN_H
#include <umicom/platform/result.h>
UmiPlatformResult umi_workspace_print_remote_plan(void);
#endif
