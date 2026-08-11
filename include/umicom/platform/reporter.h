/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/reporter.h
 *
 * PURPOSE:
 *   Print consistent human-readable status, validation and audit summaries.
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

#ifndef UMICOM_PLATFORM_REPORTER_H
#define UMICOM_PLATFORM_REPORTER_H
#include <umicom/platform/framework_audit.h>
#include <umicom/platform/validator.h>
void umi_platform_report_workspace(const UmiPlatformWorkspace *workspace);
void umi_platform_report_validation(const UmiPlatformValidationSummary *summary);
void umi_platform_report_framework_audit(const UmiFrameworkAuditSummary *summary);
#endif
