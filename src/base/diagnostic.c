/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/base/diagnostic.c
 *
 * PURPOSE:
 *   Map diagnostic severity values to readable names.
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

#include <umicom/platform/diagnostic.h>
const char *umi_platform_severity_name(UmiPlatformSeverity severity) {
    switch (severity) {
        case UMI_PLATFORM_SEVERITY_INFO: return "info";
        case UMI_PLATFORM_SEVERITY_WARNING: return "warning";
        case UMI_PLATFORM_SEVERITY_ERROR: return "error";
        default: return "unknown";
    }
}
