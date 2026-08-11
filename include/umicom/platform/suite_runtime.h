/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/suite_runtime.h
 *
 * PURPOSE:
 *   Evaluate required and optional suite members against the current platform workspace.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file keeps suite and integration orchestration explicit. The master
 * platform plans composition, but products remain independent repositories
 * communicating through Framework contracts rather than private state.
 */

#ifndef UMICOM_PLATFORM_SUITE_RUNTIME_H
#define UMICOM_PLATFORM_SUITE_RUNTIME_H

#include <stdbool.h>
#include <stddef.h>
#include <umicom/platform/workspace.h>

typedef struct UmiPlatformSuiteReadiness {
    size_t required_total;
    size_t required_available;
    size_t required_missing;
    size_t optional_total;
    size_t optional_available;
    size_t optional_missing;
    bool ready;
    bool degraded;
} UmiPlatformSuiteReadiness;

const UmiPlatformProject *umi_platform_workspace_find_project(
    const UmiPlatformWorkspace *workspace,
    const char *project_id);
const UmiPlatformSuite *umi_platform_workspace_find_suite(
    const UmiPlatformWorkspace *workspace,
    const char *suite_id);
UmiPlatformResult umi_platform_suite_readiness(
    const UmiPlatformWorkspace *workspace,
    const UmiPlatformSuite *suite,
    UmiPlatformSuiteReadiness *out_readiness);

#endif
