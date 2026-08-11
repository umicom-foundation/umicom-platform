/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/framework_audit.h
 *
 * PURPOSE:
 *   Compare root and nested Framework revisions for enabled application repositories.
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

#ifndef UMICOM_PLATFORM_FRAMEWORK_AUDIT_H
#define UMICOM_PLATFORM_FRAMEWORK_AUDIT_H
#include <umicom/platform/workspace.h>
typedef struct UmiFrameworkAuditSummary {
    size_t checked;
    size_t matched;
    size_t mismatched;
    size_t not_initialized;
} UmiFrameworkAuditSummary;
UmiPlatformResult umi_platform_framework_audit(const UmiPlatformWorkspace *workspace, UmiFrameworkAuditSummary *summary);
#endif
