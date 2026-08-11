/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/git/git.c
 *
 * PURPOSE:
 *   Read Git availability and repository HEAD revisions.
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

#include <stdio.h>
#include <string.h>
#include <umicom/platform/types.h>
#include <umicom/platform/process.h>
#include <umicom/platform/git.h>
bool umi_platform_git_available(void) {
    char output[128];
    int code = -1;
    return umi_platform_process_capture("git --version 2>&1", output, sizeof(output), &code) && code == 0;
}
bool umi_platform_git_head(const char *path, char *sha, size_t capacity) {
    if (path == NULL || sha == NULL || capacity < 41u) return false;
    char command[UMI_PLATFORM_PATH_MAX + 80u];
    const int n = snprintf(command, sizeof(command), "git -C \"%s\" rev-parse HEAD 2>&1", path);
    if (n < 0 || (size_t)n >= sizeof(command)) return false;
    int code = -1;
    if (!umi_platform_process_capture(command, sha, capacity, &code) || code != 0) return false;
    char *newline = strpbrk(sha, "\r\n");
    if (newline != NULL) *newline = '\0';
    return strlen(sha) == 40u;
}
