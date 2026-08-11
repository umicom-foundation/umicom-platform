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
