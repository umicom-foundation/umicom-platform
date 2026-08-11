/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/report/reporter.c
 *
 * PURPOSE:
 *   Print concise workspace and validation summaries.
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

#include <stdio.h>
#include <umicom/platform/reporter.h>
void umi_platform_report_workspace(const UmiPlatformWorkspace *workspace) {
    printf("Projects: %zu\n", workspace->project_count);
    for (size_t i = 0u; i < workspace->project_count; ++i) {
        const UmiPlatformProject *p = &workspace->projects[i];
        printf("  %-30s %-18s %s\n", p->id, p->status, p->path);
    }
    printf("Suites: %zu\n", workspace->suite_count);
}
void umi_platform_report_validation(const UmiPlatformValidationSummary *summary) {
    printf("Validation: checks=%zu passed=%zu warnings=%zu failed=%zu\n", summary->checks, summary->passed, summary->warnings, summary->failed);
}
void umi_platform_report_framework_audit(const UmiFrameworkAuditSummary *summary) {
    printf("Framework audit: checked=%zu matched=%zu mismatched=%zu not-initialized=%zu\n", summary->checked, summary->matched, summary->mismatched, summary->not_initialized);
}
