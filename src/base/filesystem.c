/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/base/filesystem.c
 *
 * PURPOSE:
 *   Implement portable file-system probes.
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
#include <sys/stat.h>
#include <umicom/platform/filesystem.h>
static bool stat_mode(const char *path, int want_directory) {
    struct stat st;
    if (path == NULL || stat(path, &st) != 0) return false;
#ifdef _WIN32
    return want_directory ? ((st.st_mode & _S_IFDIR) != 0) : ((st.st_mode & _S_IFREG) != 0);
#else
    return want_directory ? S_ISDIR(st.st_mode) : S_ISREG(st.st_mode);
#endif
}
bool umi_platform_path_exists(const char *path) {
    struct stat st;
    return path != NULL && stat(path, &st) == 0;
}
bool umi_platform_file_exists(const char *path) { return stat_mode(path, 0); }
bool umi_platform_directory_exists(const char *path) { return stat_mode(path, 1); }
bool umi_platform_read_text_file(const char *path, char *buffer, size_t capacity, size_t *out_length) {
    if (path == NULL || buffer == NULL || capacity < 2u) return false;
    FILE *file = fopen(path, "rb");
    if (file == NULL) return false;
    const size_t read_count = fread(buffer, 1u, capacity - 1u, file);
    const bool eof_reached = feof(file) != 0;
    fclose(file);
    if (!eof_reached && read_count == capacity - 1u) return false;
    buffer[read_count] = '\0';
    if (out_length != NULL) *out_length = read_count;
    return true;
}
