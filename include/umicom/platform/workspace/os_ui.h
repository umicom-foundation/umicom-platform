/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/os_ui.h
 *
 * PURPOSE:
 *   Explain the canonical Umicom OS Framework and GTK4 dependency boundary.
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

#ifndef UMICOM_PLATFORM_OS_UI_H
#define UMICOM_PLATFORM_OS_UI_H
void umi_workspace_print_os_ui_policy(void);
#endif
