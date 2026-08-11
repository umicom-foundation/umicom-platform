/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/validator.h
 *
 * PURPOSE:
 *   Run first-stage structural validation across workspace manifests and required paths.
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

#ifndef UMICOM_PLATFORM_VALIDATOR_H
#define UMICOM_PLATFORM_VALIDATOR_H
#include <umicom/platform/workspace.h>
typedef struct UmiPlatformValidationSummary {
    size_t checks;
    size_t passed;
    size_t warnings;
    size_t failed;
} UmiPlatformValidationSummary;
UmiPlatformResult umi_platform_validate(const UmiPlatformWorkspace *workspace, UmiPlatformValidationSummary *summary);
#endif
