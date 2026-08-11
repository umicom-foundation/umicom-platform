/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/config.h
 *
 * PURPOSE:
 *   Define canonical first-stage manifest and lock file locations.
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

#ifndef UMICOM_PLATFORM_CONFIG_H
#define UMICOM_PLATFORM_CONFIG_H
#define UMI_PLATFORM_WORKSPACE_FILE "umicom-workspace.json"
#define UMI_PLATFORM_LOCK_FILE "VERSION_LOCK.json"
#define UMI_PLATFORM_PROJECT_INDEX "manifests/projects/index.txt"
#define UMI_PLATFORM_SUITE_INDEX "manifests/suites/index.txt"
#endif
