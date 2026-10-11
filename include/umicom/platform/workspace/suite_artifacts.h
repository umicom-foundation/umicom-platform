/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/suite_artifacts.h
 *
 * PURPOSE:
 *   Describe a read-only, target-specific suite executable-artifact gate.
 *   Repository readiness is not the same as an executable being present.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_PLATFORM_WORKSPACE_SUITE_ARTIFACTS_H
#define UMICOM_PLATFORM_WORKSPACE_SUITE_ARTIFACTS_H

#include <stdbool.h>
#include <stddef.h>
#include <umicom/platform/suite_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UMI_PLATFORM_ARTIFACT_NAME_MAX 128u
#define UMI_PLATFORM_ARTIFACT_MEMBER_MAX (UMI_PLATFORM_MAX_SUITE_MEMBERS * 2u)

/* This is the intended output platform, not necessarily the build host. */
typedef enum UmiPlatformArtifactTarget {
    UMI_PLATFORM_ARTIFACT_WINDOWS = 1,
    UMI_PLATFORM_ARTIFACT_LINUX = 2
} UmiPlatformArtifactTarget;

/* A mapping has no authority to launch or execute its named file. */
typedef struct UmiPlatformArtifactEntry {
    char project_id[UMI_PLATFORM_ID_MAX];
    char windows_filename[UMI_PLATFORM_ARTIFACT_NAME_MAX];
    char linux_filename[UMI_PLATFORM_ARTIFACT_NAME_MAX];
} UmiPlatformArtifactEntry;

typedef struct UmiPlatformArtifactCatalogue {
    UmiPlatformArtifactEntry items[UMI_PLATFORM_MAX_PROJECTS];
    size_t count;
} UmiPlatformArtifactCatalogue;

typedef enum UmiPlatformArtifactState {
    UMI_PLATFORM_ARTIFACT_READY = 1,
    UMI_PLATFORM_ARTIFACT_PROJECT_UNAVAILABLE = 2,
    UMI_PLATFORM_ARTIFACT_NOT_MAPPED = 3,
    UMI_PLATFORM_ARTIFACT_NOT_FOUND = 4,
    UMI_PLATFORM_ARTIFACT_NOT_FILE = 5,
    UMI_PLATFORM_ARTIFACT_BAD_IMAGE = 6,
    UMI_PLATFORM_ARTIFACT_PATH_TOO_LONG = 7
} UmiPlatformArtifactState;

typedef struct UmiPlatformArtifactMember {
    char project_id[UMI_PLATFORM_ID_MAX];
    char artifact_path[UMI_PLATFORM_PATH_MAX];
    bool required;
    UmiPlatformArtifactState state;
} UmiPlatformArtifactMember;

typedef struct UmiPlatformSuiteArtifactReport {
    UmiPlatformArtifactMember members[UMI_PLATFORM_ARTIFACT_MEMBER_MAX];
    size_t member_count;
    size_t required_total;
    size_t required_ready;
    size_t optional_total;
    size_t optional_ready;
    bool ready;
    bool degraded;
} UmiPlatformSuiteArtifactReport;

/*
 * Read a controlled, bounded table:
 *   <project-id> <windows-exe-basename> <linux-exe-basename>
 *
 * A '-' means explicitly unmapped on that platform. Only plain filenames
 * (not paths) are allowed. The table is committed source, never downloaded.
 * On failure, out_catalogue is left untouched.
 */
UmiPlatformResult umi_platform_artifact_catalogue_load(
    const char *path, UmiPlatformArtifactCatalogue *out_catalogue);

/*
 * Check known project membership and built artefacts without launching any
 * process or changing a repository, lock, environment variable or suite.
 * Format checks are not execution, signature or malware verification.
 */
UmiPlatformResult umi_platform_suite_artifacts_evaluate(
    const UmiPlatformWorkspace *workspace,
    const UmiPlatformSuite *suite,
    const UmiPlatformArtifactCatalogue *catalogue,
    const char *bin_directory,
    UmiPlatformArtifactTarget target,
    UmiPlatformSuiteArtifactReport *out_report);

/* Return a stable display label for an inspection outcome. Extend this mapping
 * when adding a state so command-line and graphical consumers agree. */
const char *umi_platform_artifact_state_text(UmiPlatformArtifactState state);

#ifdef __cplusplus
}
#endif

#endif
