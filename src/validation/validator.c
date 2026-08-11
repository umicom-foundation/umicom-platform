/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/validation/validator.c
 *
 * PURPOSE:
 *   Coordinate first-stage workspace validation.
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

#include <string.h>
#include <umicom/platform/validator.h>
bool umi_platform_validation_project_fields(const UmiPlatformProject *project);
bool umi_platform_validation_project_path(const UmiPlatformProject *project);
bool umi_platform_validation_suite_fields(const UmiPlatformSuite *suite);
bool umi_platform_validation_root_files(void);
bool umi_platform_validation_lock_sha(void);
UmiPlatformResult umi_platform_validate(const UmiPlatformWorkspace *workspace, UmiPlatformValidationSummary *summary) {
    if (workspace == NULL || summary == NULL) return umi_platform_result_error(UMI_PLATFORM_ERROR_ARGUMENT, "validation arguments are required");
    memset(summary, 0, sizeof(*summary));
    ++summary->checks;
    if (umi_platform_validation_root_files()) ++summary->passed; else ++summary->failed;
    ++summary->checks;
    if (umi_platform_validation_lock_sha()) ++summary->passed; else ++summary->failed;
    for (size_t i = 0u; i < workspace->project_count; ++i) {
        ++summary->checks;
        if (umi_platform_validation_project_fields(&workspace->projects[i])) ++summary->passed; else ++summary->failed;
        ++summary->checks;
        if (umi_platform_validation_project_path(&workspace->projects[i])) ++summary->passed;
        else if (workspace->projects[i].enabled) ++summary->failed;
        else ++summary->warnings;
    }
    for (size_t i = 0u; i < workspace->suite_count; ++i) {
        ++summary->checks;
        if (umi_platform_validation_suite_fields(&workspace->suites[i])) ++summary->passed; else ++summary->failed;
    }
    return summary->failed == 0u ? umi_platform_result_ok() : umi_platform_result_error(UMI_PLATFORM_ERROR_VALIDATION, "workspace validation failed");
}
