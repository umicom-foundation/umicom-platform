/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/model/suite.c
 *
 * PURPOSE:
 *   Load suite manifest metadata.
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
#include <umicom/platform/filesystem.h>
#include <umicom/platform/json.h>
#include <umicom/platform/suite.h>

UmiPlatformResult umi_platform_suite_load(
    const char *path,
    UmiPlatformSuite *suite)
{
    char json[8192];

    if (path == NULL || suite == NULL) {
        return umi_platform_result_error(
            UMI_PLATFORM_ERROR_ARGUMENT,
            "suite arguments are required");
    }
    if (!umi_platform_read_text_file(
            path, json, sizeof(json), NULL)) {
        return umi_platform_result_error(
            UMI_PLATFORM_ERROR_IO,
            "cannot read suite manifest");
    }

    (void)memset(suite, 0, sizeof(*suite));
    if (!umi_platform_json_get_string(
            json, "id", suite->id, sizeof(suite->id))) {
        return umi_platform_result_error(
            UMI_PLATFORM_ERROR_PARSE, "suite id missing");
    }
    if (!umi_platform_json_get_string(
            json, "name", suite->name, sizeof(suite->name))) {
        return umi_platform_result_error(
            UMI_PLATFORM_ERROR_PARSE, "suite name missing");
    }
    if (!umi_platform_json_get_string(
            json, "status", suite->status, sizeof(suite->status))) {
        return umi_platform_result_error(
            UMI_PLATFORM_ERROR_PARSE, "suite status missing");
    }

    (void)umi_platform_json_get_bool(
        json, "enabled", &suite->enabled);

    if (!umi_platform_json_get_string_array(
            json,
            "required_members",
            suite->required_members,
            UMI_PLATFORM_MAX_SUITE_MEMBERS,
            &suite->required_member_count)) {
        return umi_platform_result_error(
            UMI_PLATFORM_ERROR_PARSE,
            "suite required_members missing or invalid");
    }

    if (!umi_platform_json_get_string_array(
            json,
            "optional_members",
            suite->optional_members,
            UMI_PLATFORM_MAX_SUITE_MEMBERS,
            &suite->optional_member_count)) {
        return umi_platform_result_error(
            UMI_PLATFORM_ERROR_PARSE,
            "suite optional_members missing or invalid");
    }

    return umi_platform_result_ok();
}
