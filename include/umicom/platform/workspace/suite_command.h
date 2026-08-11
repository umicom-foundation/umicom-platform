/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/suite_command.h
 *
 * PURPOSE:
 *   Dispatch suite list/show/plan/validate commands from the native workspace tool.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file keeps suite and integration orchestration explicit. The master
 * platform plans composition, but products remain independent repositories
 * communicating through Framework contracts rather than private state.
 */

#ifndef UMICOM_PLATFORM_WORKSPACE_SUITE_COMMAND_H
#define UMICOM_PLATFORM_WORKSPACE_SUITE_COMMAND_H
int umi_workspace_suite_command(int argc, char **argv);
#endif
