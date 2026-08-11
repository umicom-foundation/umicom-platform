/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/parse/json.c
 *
 * PURPOSE:
 *   Extract bounded fields from controlled JSON manifests.
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

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <umicom/platform/json.h>
static const char *find_value(const char *json, const char *key) {
    if (json == NULL || key == NULL) return NULL;
    char needle[160];
    const int n = snprintf(needle, sizeof(needle), "\"%s\"", key);
    if (n < 0 || (size_t)n >= sizeof(needle)) return NULL;
    const char *position = strstr(json, needle);
    if (position == NULL) return NULL;
    position += strlen(needle);
    while (*position != '\0' && isspace((unsigned char)*position)) ++position;
    if (*position++ != ':') return NULL;
    while (*position != '\0' && isspace((unsigned char)*position)) ++position;
    return position;
}
bool umi_platform_json_get_string(const char *json, const char *key, char *output, size_t capacity) {
    if (output == NULL || capacity == 0u) return false;
    const char *value = find_value(json, key);
    if (value == NULL || *value != '"') return false;
    ++value;
    const char *end = strchr(value, '"');
    if (end == NULL) return false;
    const size_t len = (size_t)(end - value);
    if (len + 1u > capacity) return false;
    memcpy(output, value, len);
    output[len] = '\0';
    return true;
}
bool umi_platform_json_get_bool(const char *json, const char *key, bool *output) {
    const char *value = find_value(json, key);
    if (value == NULL || output == NULL) return false;
    if (strncmp(value, "true", 4u) == 0) { *output = true; return true; }
    if (strncmp(value, "false", 5u) == 0) { *output = false; return true; }
    return false;
}

bool umi_platform_json_get_string_array(
    const char *json,
    const char *key,
    char output[][UMI_PLATFORM_ID_MAX],
    size_t maximum_items,
    size_t *out_count)
{
    const char *value;
    size_t count = 0U;

    if (json == NULL || key == NULL || output == NULL ||
        maximum_items == 0U || out_count == NULL) {
        return false;
    }
    *out_count = 0U;

    value = find_value(json, key);
    if (value == NULL || *value != '[') {
        return false;
    }
    ++value;

    for (;;) {
        const char *end;
        size_t length;

        while (*value != '\0' &&
               (isspace((unsigned char)*value) != 0 || *value == ',')) {
            ++value;
        }
        if (*value == ']') {
            *out_count = count;
            return true;
        }
        if (*value != '"' || count >= maximum_items) {
            return false;
        }

        ++value;
        end = strchr(value, '"');
        if (end == NULL) {
            return false;
        }
        length = (size_t)(end - value);
        if (length == 0U || length >= UMI_PLATFORM_ID_MAX) {
            return false;
        }
        (void)memcpy(output[count], value, length);
        output[count][length] = '\0';
        ++count;
        value = end + 1;
    }
}
