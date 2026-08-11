/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/git_command.c
 *
 * PURPOSE:
 *   Centralise bounded Git command execution.
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

#include <stdio.h>
#include <umicom/platform/process.h>
#include <umicom/platform/workspace/git_command.h>
bool umi_git_command_capture(const char *arguments, char *output, size_t capacity, int *exit_code) {
    if (arguments == NULL || output == NULL) return false;
    char command[2048];
    const int n=snprintf(command,sizeof(command),"git %s 2>&1",arguments);
    if(n<0 || (size_t)n>=sizeof(command)) return false;
    return umi_platform_process_capture(command,output,capacity,exit_code);
}
bool umi_git_command_run(const char *arguments, int *exit_code) {
    char output[8192];
    if(!umi_git_command_capture(arguments,output,sizeof(output),exit_code)) return false;
    fputs(output,stdout);
    return true;
}
