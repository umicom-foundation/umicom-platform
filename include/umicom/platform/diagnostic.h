/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/diagnostic.h
 *
 * PURPOSE:
 *   Provide a tiny diagnostic severity model for future structured reporting.
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

#ifndef UMICOM_PLATFORM_DIAGNOSTIC_H
#define UMICOM_PLATFORM_DIAGNOSTIC_H
typedef enum UmiPlatformSeverity {
    UMI_PLATFORM_SEVERITY_INFO,
    UMI_PLATFORM_SEVERITY_WARNING,
    UMI_PLATFORM_SEVERITY_ERROR
} UmiPlatformSeverity;
const char *umi_platform_severity_name(UmiPlatformSeverity severity);
#endif
