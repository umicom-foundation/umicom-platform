/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/workspace_command.h
 *
 * PURPOSE:
 *   Dispatch nested `workspace` commands while preserving the existing top-level CLI.
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

#ifndef UMICOM_PLATFORM_WORKSPACE_COMMAND_H
#define UMICOM_PLATFORM_WORKSPACE_COMMAND_H
int umi_platform_workspace_command(int argc, char **argv);
#endif
