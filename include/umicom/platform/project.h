/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/project.h
 *
 * PURPOSE:
 *   Provide project classification helpers used by list, validation and reporting commands.
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

#ifndef UMICOM_PLATFORM_PROJECT_H
#define UMICOM_PLATFORM_PROJECT_H
#include <umicom/platform/types.h>
bool umi_platform_project_is_planned(const UmiPlatformProject *project);
bool umi_platform_project_requires_path(const UmiPlatformProject *project);
#endif
