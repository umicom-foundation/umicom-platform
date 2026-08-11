/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/types.h
 *
 * PURPOSE:
 *   Define bounded common data structures used by the platform bootstrap tool.
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

#ifndef UMICOM_PLATFORM_TYPES_H
#define UMICOM_PLATFORM_TYPES_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define UMI_PLATFORM_PATH_MAX 1024u
#define UMI_PLATFORM_ID_MAX 96u
#define UMI_PLATFORM_NAME_MAX 160u
#define UMI_PLATFORM_REPO_MAX 256u
#define UMI_PLATFORM_STATUS_MAX 48u
#define UMI_PLATFORM_SHA_MAX 41u
#define UMI_PLATFORM_MAX_PROJECTS 128u
#define UMI_PLATFORM_MAX_SUITES 32u
#define UMI_PLATFORM_MAX_SUITE_MEMBERS 64u
typedef struct UmiPlatformProject {
    char id[UMI_PLATFORM_ID_MAX];
    char name[UMI_PLATFORM_NAME_MAX];
    char type[UMI_PLATFORM_STATUS_MAX];
    char path[UMI_PLATFORM_PATH_MAX];
    char repository[UMI_PLATFORM_REPO_MAX];
    char status[UMI_PLATFORM_STATUS_MAX];
    bool enabled;
    bool framework_required;
} UmiPlatformProject;
typedef struct UmiPlatformSuite {
    char id[UMI_PLATFORM_ID_MAX];
    char name[UMI_PLATFORM_NAME_MAX];
    char status[UMI_PLATFORM_STATUS_MAX];
    bool enabled;
    char required_members[UMI_PLATFORM_MAX_SUITE_MEMBERS][UMI_PLATFORM_ID_MAX];
    size_t required_member_count;
    char optional_members[UMI_PLATFORM_MAX_SUITE_MEMBERS][UMI_PLATFORM_ID_MAX];
    size_t optional_member_count;
} UmiPlatformSuite;
#endif
