/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/process.h
 *
 * PURPOSE:
 *   Run short read-only child commands such as git and tool version probes.
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

#ifndef UMICOM_PLATFORM_PROCESS_H
#define UMICOM_PLATFORM_PROCESS_H
#include <stdbool.h>
#include <stddef.h>
bool umi_platform_process_capture(const char *command, char *output, size_t capacity, int *exit_code);
#endif
