/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/manifest.h
 *
 * PURPOSE:
 *   Load a single project manifest into a small platform project structure.
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

#ifndef UMICOM_PLATFORM_MANIFEST_H
#define UMICOM_PLATFORM_MANIFEST_H
#include <umicom/platform/result.h>
UmiPlatformResult umi_platform_manifest_load_project(const char *path, UmiPlatformProject *project);
#endif
