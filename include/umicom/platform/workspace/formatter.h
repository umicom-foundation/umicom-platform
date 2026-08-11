/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/formatter.h
 *
 * PURPOSE:
 *   Provide small formatting helpers for consistent plan and status output.
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

#ifndef UMICOM_PLATFORM_FORMATTER_H
#define UMICOM_PLATFORM_FORMATTER_H
void umi_workspace_print_heading(const char *text);
void umi_workspace_print_key_value(const char *key, const char *value);
void umi_workspace_print_boolean(const char *key, int value);
#endif
