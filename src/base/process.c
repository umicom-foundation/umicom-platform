/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/base/process.c
 *
 * PURPOSE:
 *   Capture output from short read-only child commands.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file is part of the bootstrap layer for the Umicom Platform workspace.
 * The code is intentionally small and explicit so a new developer can follow
 * how the platform discovers projects, validates files and reports problems.
 */

#ifndef _WIN32
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#endif
#include <stdio.h>
#include <string.h>
#include <umicom/platform/process.h>
#ifdef _WIN32
#define UMI_POPEN _popen
#define UMI_PCLOSE _pclose
#else
#include <sys/wait.h>
#define UMI_POPEN popen
#define UMI_PCLOSE pclose
#endif
bool umi_platform_process_capture(const char *command, char *output, size_t capacity, int *exit_code) {
    if (command == NULL || output == NULL || capacity == 0u) return false;
    output[0] = '\0';
    FILE *pipe = UMI_POPEN(command, "r");
    if (pipe == NULL) return false;
    size_t used = 0u;
    while (used + 1u < capacity) {
        const size_t n = fread(output + used, 1u, capacity - used - 1u, pipe);
        used += n;
        if (n == 0u) break;
    }
    output[used] = '\0';
    const int status = UMI_PCLOSE(pipe);
#ifdef _WIN32
    if (exit_code != NULL) *exit_code = status;
#else
    if (exit_code != NULL) *exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : status;
#endif
    return true;
}
