/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/validation/suite_validator.c
 *
 * PURPOSE:
 *   Validate suite manifest fields.
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
#include <umicom/platform/suite.h>

bool umi_platform_validation_suite_fields(const UmiPlatformSuite *suite)
{
    size_t i;
    size_t j;

    if (suite == NULL || suite->id[0] == '\0' ||
        suite->name[0] == '\0' || suite->status[0] == '\0' ||
        suite->required_member_count == 0U) {
        return false;
    }

    for (i = 0U; i < suite->required_member_count; ++i) {
        if (suite->required_members[i][0] == '\0') {
            return false;
        }
        for (j = i + 1U; j < suite->required_member_count; ++j) {
            if (strcmp(suite->required_members[i],
                       suite->required_members[j]) == 0) {
                return false;
            }
        }
        for (j = 0U; j < suite->optional_member_count; ++j) {
            if (strcmp(suite->required_members[i],
                       suite->optional_members[j]) == 0) {
                return false;
            }
        }
    }

    for (i = 0U; i < suite->optional_member_count; ++i) {
        if (suite->optional_members[i][0] == '\0') {
            return false;
        }
        for (j = i + 1U; j < suite->optional_member_count; ++j) {
            if (strcmp(suite->optional_members[i],
                       suite->optional_members[j]) == 0) {
                return false;
            }
        }
    }
    return true;
}
