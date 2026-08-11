/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace.h
 *
 * PURPOSE:
 *   Discover project and suite manifests from the platform index files.
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

#ifndef UMICOM_PLATFORM_WORKSPACE_H
#define UMICOM_PLATFORM_WORKSPACE_H
#include <umicom/platform/result.h>
typedef struct UmiPlatformWorkspace {
    UmiPlatformProject projects[UMI_PLATFORM_MAX_PROJECTS];
    size_t project_count;
    UmiPlatformSuite suites[UMI_PLATFORM_MAX_SUITES];
    size_t suite_count;
} UmiPlatformWorkspace;
UmiPlatformResult umi_platform_workspace_load(UmiPlatformWorkspace *workspace);
#endif
