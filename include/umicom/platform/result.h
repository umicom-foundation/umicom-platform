/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/result.h
 *
 * PURPOSE:
 *   Provide explicit success/failure results for bootstrap operations.
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

#ifndef UMICOM_PLATFORM_RESULT_H
#define UMICOM_PLATFORM_RESULT_H
#include <umicom/platform/types.h>
typedef enum UmiPlatformResultCode {
    UMI_PLATFORM_OK = 0,
    UMI_PLATFORM_ERROR_ARGUMENT = 1,
    UMI_PLATFORM_ERROR_IO = 2,
    UMI_PLATFORM_ERROR_PARSE = 3,
    UMI_PLATFORM_ERROR_NOT_FOUND = 4,
    UMI_PLATFORM_ERROR_VALIDATION = 5,
    UMI_PLATFORM_ERROR_PROCESS = 6
} UmiPlatformResultCode;
typedef struct UmiPlatformResult {
    UmiPlatformResultCode code;
    char message[256];
} UmiPlatformResult;
UmiPlatformResult umi_platform_result_ok(void);
UmiPlatformResult umi_platform_result_error(UmiPlatformResultCode code, const char *message);
bool umi_platform_result_is_ok(UmiPlatformResult result);
#endif
