/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/suite_artifacts.c
 *
 * PURPOSE:
 *   Implement fail-closed suite executable-artifact readiness without any
 *   process launch. Tests and product packaging retain their separate duties.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include <umicom/platform/filesystem.h>
#include <umicom/platform/path.h>
#include <umicom/platform/workspace/suite_artifacts.h>

/* Treat the declarative inventory as untrusted text, even though it is local.
 * No shell, directory separator, volume prefix or relative traversal belongs
 * inside a proposed executable filename. Product paths remain separate. */
static bool identifier_valid(const char *value)
{
    size_t i;
    if (value == NULL || value[0] == '\0') {
        return false;
    }
    for (i = 0u; value[i] != '\0'; ++i) {
        const unsigned char c = (unsigned char)value[i];
        const bool ascii_letter = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
        const bool ascii_digit = c >= '0' && c <= '9';
        if (!(ascii_letter || ascii_digit || c == '.' || c == '_' || c == '-')) {
            return false;
        }
    }
    return true;
}

static bool filename_valid(const char *value)
{
    if (value == NULL || value[0] == '\0') {
        return false;
    }
    if (strcmp(value, "-") == 0) {
        return true;  /* Explicitly not supported/mapped on this target. */
    }
    if (strcmp(value, ".") == 0 || strcmp(value, "..") == 0) {
        return false;
    }
    return identifier_valid(value);
}

static bool catalogue_duplicate(const UmiPlatformArtifactCatalogue *catalogue,
                                const char *project_id)
{
    size_t i;
    for (i = 0u; i < catalogue->count; ++i) {
        if (strcmp(catalogue->items[i].project_id, project_id) == 0) {
            return true;
        }
    }
    return false;
}

UmiPlatformResult umi_platform_artifact_catalogue_load(
    const char *path, UmiPlatformArtifactCatalogue *out_catalogue)
{
    UmiPlatformArtifactCatalogue next;
    FILE *file;
    char line[512];
    if (path == NULL || path[0] == '\0' || out_catalogue == NULL) {
        return umi_platform_result_error(UMI_PLATFORM_ERROR_ARGUMENT,
                                         "artifact catalogue path and output are required");
    }
    file = fopen(path, "rb");
    if (file == NULL) {
        return umi_platform_result_error(UMI_PLATFORM_ERROR_IO,
                                         "cannot open executable artifact catalogue");
    }
    (void)memset(&next, 0, sizeof(next));
    while (fgets(line, sizeof(line), file) != NULL) {
        UmiPlatformArtifactEntry item;
        char extra;
        const char *begin = line;
        size_t length = strlen(line);
        int consumed;
        /* Detect line truncation; it must never silently form two records. */
        if (length != 0u && line[length - 1u] != '\n' && !feof(file)) {
            (void)fclose(file);
            return umi_platform_result_error(UMI_PLATFORM_ERROR_PARSE,
                                             "executable catalogue line exceeds limit");
        }
        while (*begin == ' ' || *begin == '\t' || *begin == '\r' ||
               *begin == '\n' || *begin == '\v' || *begin == '\f') {
            ++begin;
        }
        if (*begin == '\0' || *begin == '#') {
            continue;
        }
        (void)memset(&item, 0, sizeof(item));
        consumed = sscanf(begin, "%95s %127s %127s %c",
                          item.project_id, item.windows_filename,
                          item.linux_filename, &extra);
        if (consumed != 3 || !identifier_valid(item.project_id) ||
            !filename_valid(item.windows_filename) ||
            !filename_valid(item.linux_filename) ||
            catalogue_duplicate(&next, item.project_id) ||
            next.count >= UMI_PLATFORM_MAX_PROJECTS) {
            (void)fclose(file);
            return umi_platform_result_error(UMI_PLATFORM_ERROR_PARSE,
                                             "invalid/duplicate artifact catalogue entry");
        }
        next.items[next.count] = item;
        ++next.count;
    }
    if (ferror(file) != 0) {
        (void)fclose(file);
        return umi_platform_result_error(UMI_PLATFORM_ERROR_IO,
                                         "failed reading executable catalogue");
    }
    (void)fclose(file);
    *out_catalogue = next;
    return umi_platform_result_ok();
}

static const UmiPlatformArtifactEntry *find_artifact(
    const UmiPlatformArtifactCatalogue *catalogue, const char *project_id)
{
    size_t i;
    for (i = 0u; i < catalogue->count; ++i) {
        if (strcmp(catalogue->items[i].project_id, project_id) == 0) {
            return &catalogue->items[i];
        }
    }
    return NULL;
}

static bool file_regular(const char *path, UmiPlatformArtifactTarget target)
{
    struct stat info;
    if (stat(path, &info) != 0) {
        return false;
    }
#ifdef _WIN32
    (void)target;
    return (info.st_mode & _S_IFREG) != 0;
#else
    return S_ISREG(info.st_mode) &&
           (target != UMI_PLATFORM_ARTIFACT_LINUX || (info.st_mode & 0111) != 0);
#endif
}

/* Read untrusted binary metadata in bounded chunks; no mmap or execution. */
static bool image_signature_valid(const char *path, UmiPlatformArtifactTarget target)
{
    unsigned char header[64];
    FILE *file = fopen(path, "rb");
    bool valid = false;
    if (file == NULL) {
        return false;
    }
    if (fread(header, 1u, sizeof(header), file) != sizeof(header)) {
        (void)fclose(file);
        return false;
    }
    if (target == UMI_PLATFORM_ARTIFACT_LINUX) {
        const unsigned type = (unsigned)header[16] | ((unsigned)header[17] << 8u);
        const unsigned machine = (unsigned)header[18] | ((unsigned)header[19] << 8u);
        valid = header[0] == 0x7fu && header[1] == 'E' &&
                header[2] == 'L' && header[3] == 'F' &&
                (header[4] == 1u || header[4] == 2u) &&
                header[5] == 1u && header[6] == 1u &&
                (type == 2u || type == 3u) && machine != 0u;
    } else if (target == UMI_PLATFORM_ARTIFACT_WINDOWS) {
        uint32_t pe_offset;
        unsigned char coff[24];
        long length;
        unsigned machine;
        unsigned characteristics;
        unsigned optional_length;
        /* DOS header points to PE/COFF. An arbitrary MZ file is insufficient. */
        pe_offset = (uint32_t)header[60] | ((uint32_t)header[61] << 8u) |
                    ((uint32_t)header[62] << 16u) | ((uint32_t)header[63] << 24u);
        if (header[0] == 'M' && header[1] == 'Z' &&
            pe_offset >= 64u && pe_offset <= 1024u * 1024u &&
            fseek(file, 0L, SEEK_END) == 0 && (length = ftell(file)) >= 0 &&
            (uint64_t)length >= (uint64_t)pe_offset + sizeof(coff) &&
            fseek(file, (long)pe_offset, SEEK_SET) == 0 &&
            fread(coff, 1u, sizeof(coff), file) == sizeof(coff)) {
            machine = (unsigned)coff[4] | ((unsigned)coff[5] << 8u);
            characteristics = (unsigned)coff[22] | ((unsigned)coff[23] << 8u);
            optional_length = (unsigned)coff[20] | ((unsigned)coff[21] << 8u);
            valid = coff[0] == 'P' && coff[1] == 'E' &&
                    coff[2] == 0u && coff[3] == 0u &&
                    (machine == 0x8664u || machine == 0x14cu || machine == 0xaa64u) &&
                    (characteristics & 0x0002u) != 0u &&
                    optional_length >= 2u &&
                    (uint64_t)length >= (uint64_t)pe_offset + sizeof(coff) + optional_length;
        }
    }
    (void)fclose(file);
    return valid;
}

static UmiPlatformArtifactState evaluate_member(
    const UmiPlatformWorkspace *workspace,
    const UmiPlatformArtifactCatalogue *catalogue,
    const char *bin_directory,
    UmiPlatformArtifactTarget target,
    UmiPlatformArtifactMember *member)
{
    const UmiPlatformProject *project;
    const UmiPlatformArtifactEntry *artifact;
    const char *filename;
    char built_path[UMI_PLATFORM_PATH_MAX];

    project = umi_platform_workspace_find_project(workspace, member->project_id);
    if (project == NULL || !project->enabled || project->path[0] == '\0' ||
        !umi_platform_directory_exists(project->path)) {
        return UMI_PLATFORM_ARTIFACT_PROJECT_UNAVAILABLE;
    }
    artifact = find_artifact(catalogue, member->project_id);
    if (artifact == NULL) {
        return UMI_PLATFORM_ARTIFACT_NOT_MAPPED;
    }
    filename = target == UMI_PLATFORM_ARTIFACT_WINDOWS
             ? artifact->windows_filename : artifact->linux_filename;
    if (strcmp(filename, "-") == 0) {
        return UMI_PLATFORM_ARTIFACT_NOT_MAPPED;
    }
    if (!umi_platform_path_join(built_path, sizeof(built_path),
                                bin_directory, filename)) {
        return UMI_PLATFORM_ARTIFACT_PATH_TOO_LONG;
    }
    (void)memcpy(member->artifact_path, built_path, strlen(built_path) + 1u);
    if (!umi_platform_path_exists(built_path)) {
        return UMI_PLATFORM_ARTIFACT_NOT_FOUND;
    }
    if (!file_regular(built_path, target)) {
        return UMI_PLATFORM_ARTIFACT_NOT_FILE;
    }
    if (!image_signature_valid(built_path, target)) {
        return UMI_PLATFORM_ARTIFACT_BAD_IMAGE;
    }
    return UMI_PLATFORM_ARTIFACT_READY;
}

UmiPlatformResult umi_platform_suite_artifacts_evaluate(
    const UmiPlatformWorkspace *workspace,
    const UmiPlatformSuite *suite,
    const UmiPlatformArtifactCatalogue *catalogue,
    const char *bin_directory,
    UmiPlatformArtifactTarget target,
    UmiPlatformSuiteArtifactReport *out_report)
{
    UmiPlatformSuiteArtifactReport next;
    size_t index;
    size_t total;
    if (workspace == NULL || suite == NULL || catalogue == NULL ||
        bin_directory == NULL || bin_directory[0] == '\0' ||
        out_report == NULL ||
        (target != UMI_PLATFORM_ARTIFACT_WINDOWS &&
         target != UMI_PLATFORM_ARTIFACT_LINUX) ||
        catalogue->count > UMI_PLATFORM_MAX_PROJECTS ||
        workspace->project_count > UMI_PLATFORM_MAX_PROJECTS ||
        workspace->suite_count > UMI_PLATFORM_MAX_SUITES ||
        suite->required_member_count > UMI_PLATFORM_MAX_SUITE_MEMBERS ||
        suite->optional_member_count > UMI_PLATFORM_MAX_SUITE_MEMBERS) {
        return umi_platform_result_error(UMI_PLATFORM_ERROR_ARGUMENT,
                                         "invalid suite artifact readiness arguments");
    }
    /* A public caller could construct these arrays directly rather than
     * using the vetted manifest loader. Validate their bounds and uniqueness
     * before any strcmp, strlen, stat or other unbounded operation. */
    for (index = 0u; index < workspace->project_count; ++index) {
        const UmiPlatformProject *project = &workspace->projects[index];
        if (memchr(project->id, '\0', sizeof(project->id)) == NULL ||
            memchr(project->path, '\0', sizeof(project->path)) == NULL ||
            !identifier_valid(project->id)) {
            return umi_platform_result_error(UMI_PLATFORM_ERROR_VALIDATION,
                                             "invalid project metadata in workspace");
        }
    }
    for (index = 0u; index < catalogue->count; ++index) {
        const UmiPlatformArtifactEntry *entry = &catalogue->items[index];
        size_t earlier;
        if (memchr(entry->project_id, '\0', sizeof(entry->project_id)) == NULL ||
            memchr(entry->windows_filename, '\0', sizeof(entry->windows_filename)) == NULL ||
            memchr(entry->linux_filename, '\0', sizeof(entry->linux_filename)) == NULL ||
            !identifier_valid(entry->project_id) ||
            !filename_valid(entry->windows_filename) ||
            !filename_valid(entry->linux_filename)) {
            return umi_platform_result_error(UMI_PLATFORM_ERROR_VALIDATION,
                                             "invalid executable catalogue metadata");
        }
        for (earlier = 0u; earlier < index; ++earlier) {
            if (strcmp(catalogue->items[earlier].project_id, entry->project_id) == 0) {
                return umi_platform_result_error(UMI_PLATFORM_ERROR_VALIDATION,
                                                 "duplicate executable catalogue project");
            }
        }
    }
    (void)memset(&next, 0, sizeof(next));
    next.required_total = suite->required_member_count;
    next.optional_total = suite->optional_member_count;
    total = next.required_total + next.optional_total;
    for (index = 0u; index < total; ++index) {
        UmiPlatformArtifactMember *member = &next.members[index];
        const char *id = index < next.required_total
                       ? suite->required_members[index]
                       : suite->optional_members[index - next.required_total];
        /* Malformed or hostile IDs must not reach the catalogue lookup. */
        if (memchr(id, '\0', UMI_PLATFORM_ID_MAX) == NULL ||
            !identifier_valid(id)) {
            return umi_platform_result_error(UMI_PLATFORM_ERROR_VALIDATION,
                                             "suite contains invalid project identifier");
        }
        for (size_t previous = 0u; previous < index; ++previous) {
            if (strcmp(next.members[previous].project_id, id) == 0) {
                return umi_platform_result_error(UMI_PLATFORM_ERROR_VALIDATION,
                                                 "suite repeats the same project identifier");
            }
        }
        (void)memcpy(member->project_id, id, strlen(id) + 1u);
        member->required = index < next.required_total;
        member->state = evaluate_member(workspace, catalogue, bin_directory,
                                         target, member);
        if (member->state == UMI_PLATFORM_ARTIFACT_READY) {
            if (member->required) {
                ++next.required_ready;
            } else {
                ++next.optional_ready;
            }
        }
        ++next.member_count;
    }
    next.ready = suite->enabled && next.required_ready == next.required_total;
    next.degraded = next.ready && next.optional_ready != next.optional_total;
    *out_report = next;
    return umi_platform_result_ok();
}

const char *umi_platform_artifact_state_text(UmiPlatformArtifactState state)
{
    switch (state) {
        case UMI_PLATFORM_ARTIFACT_READY: return "READY-IMAGE";
        case UMI_PLATFORM_ARTIFACT_PROJECT_UNAVAILABLE: return "PROJECT-UNAVAILABLE";
        case UMI_PLATFORM_ARTIFACT_NOT_MAPPED: return "UNMAPPED";
        case UMI_PLATFORM_ARTIFACT_NOT_FOUND: return "MISSING-BINARY";
        case UMI_PLATFORM_ARTIFACT_NOT_FILE: return "NOT-EXECUTABLE-FILE";
        case UMI_PLATFORM_ARTIFACT_BAD_IMAGE: return "UNRECOGNISED-IMAGE";
        case UMI_PLATFORM_ARTIFACT_PATH_TOO_LONG: return "PATH-TOO-LONG";
        default: return "INVALID";
    }
}
