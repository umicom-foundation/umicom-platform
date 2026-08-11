/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/base/path.c
 *
 * PURPOSE:
 *   Implement safe repository-relative path handling.
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
#include <string.h>
#include <umicom/platform/path.h>
bool umi_platform_path_join(char *output, size_t capacity, const char *left, const char *right) {
    if (output == NULL || left == NULL || right == NULL || capacity == 0u) return false;
    const char separator =
#ifdef _WIN32
        '\\';
#else
        '/';
#endif
    ;
    const size_t left_len = strlen(left);
    const bool already_sep = left_len > 0u && (left[left_len - 1u] == '/' || left[left_len - 1u] == '\\');
    int written = 0;
    if (already_sep) {
        written = snprintf(output, capacity, "%s%s", left, right);
    } else {
        written = snprintf(output, capacity, "%s%c%s", left, separator, right);
    }
    return written >= 0 && (size_t)written < capacity;
}
bool umi_platform_path_is_safe_relative(const char *path) {
    if (path == NULL || path[0] == '\0') return false;
    if (path[0] == '/' || path[0] == '\\') return false;
    if (strstr(path, "..") != NULL) return false;
    if (strlen(path) > 1u && path[1] == ':') return false;
    return true;
}
