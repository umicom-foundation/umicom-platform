/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/lock.h
 *
 * PURPOSE:
 *   Expose the pinned root Framework SHA from VERSION_LOCK for consistency checks.
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

#ifndef UMICOM_PLATFORM_LOCK_H
#define UMICOM_PLATFORM_LOCK_H
#include <umicom/platform/result.h>
UmiPlatformResult umi_platform_lock_framework_sha(char *output, size_t capacity);
#endif
