/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/git_command.h
 *
 * PURPOSE:
 *   Centralise safe fixed Git command execution used by workspace orchestration.
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

#ifndef UMICOM_PLATFORM_GIT_COMMAND_H
#define UMICOM_PLATFORM_GIT_COMMAND_H
#include <stdbool.h>
#include <stddef.h>
bool umi_git_command_capture(const char *arguments, char *output, size_t capacity, int *exit_code);
bool umi_git_command_run(const char *arguments, int *exit_code);
#endif
