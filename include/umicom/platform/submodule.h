/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/submodule.h
 *
 * PURPOSE:
 *   Detect whether a nested Git submodule working tree has been initialised.
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

#ifndef UMICOM_PLATFORM_SUBMODULE_H
#define UMICOM_PLATFORM_SUBMODULE_H
#include <stdbool.h>
bool umi_platform_submodule_initialized(const char *path);
#endif
