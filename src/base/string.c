/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/base/string.c
 *
 * PURPOSE:
 *   Implement bounded string operations.
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
#include <string.h>
#include <umicom/platform/string.h>
bool umi_platform_string_copy(char *destination, size_t capacity, const char *source) {
    if (destination == NULL || source == NULL || capacity == 0u) return false;
    const size_t length = strlen(source);
    if (length + 1u > capacity) return false;
    memcpy(destination, source, length + 1u);
    return true;
}
bool umi_platform_string_equal(const char *left, const char *right) {
    return left != NULL && right != NULL && strcmp(left, right) == 0;
}
bool umi_platform_string_starts_with(const char *text, const char *prefix) {
    if (text == NULL || prefix == NULL) return false;
    const size_t n = strlen(prefix);
    return strncmp(text, prefix, n) == 0;
}
void umi_platform_string_trim(char *text) {
    if (text == NULL) return;
    char *start = text;
    while (*start != '\0' && isspace((unsigned char)*start)) ++start;
    if (start != text) memmove(text, start, strlen(start) + 1u);
    size_t len = strlen(text);
    while (len > 0u && isspace((unsigned char)text[len - 1u])) text[--len] = '\0';
}
