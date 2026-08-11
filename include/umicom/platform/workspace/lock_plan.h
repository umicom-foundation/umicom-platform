/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/lock_plan.h
 *
 * PURPOSE:
 *   Collect local project HEAD revisions without writing VERSION_LOCK automatically.
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

#ifndef UMICOM_PLATFORM_LOCK_PLAN_H
#define UMICOM_PLATFORM_LOCK_PLAN_H
#include <umicom/platform/result.h>
UmiPlatformResult umi_workspace_print_lock_plan(void);
#endif
