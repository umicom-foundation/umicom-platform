/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_suite_artifacts.c
 *
 * PURPOSE:
 *   Validate the read-only executable artifact gate, including strict
 *   catalogue input, target image checks and required/optional semantics.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <umi_test.h>
#include <umicom/platform/workspace/suite_artifacts.h>

#ifdef _WIN32
#include <direct.h>
#define TEST_MKDIR(path) _mkdir(path)
#define TEST_RMDIR(path) _rmdir(path)
#define TEST_CHMOD(path) ((void)(path), 0)
#else
#include <unistd.h>
#define TEST_MKDIR(path) mkdir(path, 0700)
#define TEST_RMDIR(path) rmdir(path)
#define TEST_CHMOD(path) chmod(path, 0755)
#endif

#define DIRECTORY ".umicom-suite-artifact-tests"
#define CATALOGUE DIRECTORY "/catalogue.txt"
#define LINUX_BIN DIRECTORY "/umicom-test"
#define WINDOWS_BIN DIRECTORY "/umicom-test.exe"

static bool write_file(const char *path, const void *data, size_t length)
{
    FILE *file = fopen(path, "wb");
    bool ok;
    if (file == NULL) {
        return false;
    }
    ok = fwrite(data, 1u, length, file) == length;
    ok = fclose(file) == 0 && ok;
    return ok;
}

static bool write_text(const char *path, const char *text)
{
    return write_file(path, text, strlen(text));
}

/* An ELF-shaped fixture, NOT a runnable program: the test verifies only the
 * advertised bounded header recognition, never executable viability. */
static bool write_elf(const char *path)
{
    unsigned char bytes[128] = {0};
    bytes[0] = 0x7f;
    bytes[1] = 'E';
    bytes[2] = 'L';
    bytes[3] = 'F';
    bytes[4] = 2u;   /* ELFCLASS64 */
    bytes[5] = 1u;   /* little-endian */
    bytes[6] = 1u;   /* ELF version */
    bytes[16] = 2u;  /* ET_EXEC */
    bytes[18] = 0x3eu; /* x86-64 */
    return write_file(path, bytes, sizeof(bytes)) && TEST_CHMOD(path) == 0;
}

/* PE-shaped fixture, NOT a runnable Windows application. */
static bool write_pe(const char *path)
{
    unsigned char bytes[512] = {0};
    bytes[0] = 'M';
    bytes[1] = 'Z';
    bytes[0x3c] = 0x80;
    bytes[0x80] = 'P';
    bytes[0x81] = 'E';
    bytes[0x84] = 0x64;
    bytes[0x85] = 0x86; /* x86-64 */
    bytes[0x94] = 0xe0; /* PE optional header length */
    bytes[0x96] = 0x02; /* IMAGE_FILE_EXECUTABLE_IMAGE */
    return write_file(path, bytes, sizeof(bytes));
}

static void init_workspace(UmiPlatformWorkspace *workspace, UmiPlatformSuite *suite)
{
    (void)memset(workspace, 0, sizeof(*workspace));
    (void)memset(suite, 0, sizeof(*suite));
    workspace->project_count = 2u;
    (void)snprintf(workspace->projects[0].id,
                   sizeof(workspace->projects[0].id), "%s", "umicom.test");
    (void)snprintf(workspace->projects[0].path,
                   sizeof(workspace->projects[0].path), "%s", DIRECTORY);
    workspace->projects[0].enabled = true;
    (void)snprintf(workspace->projects[1].id,
                   sizeof(workspace->projects[1].id), "%s", "umicom.optional");
    (void)snprintf(workspace->projects[1].path,
                   sizeof(workspace->projects[1].path), "%s", DIRECTORY);
    workspace->projects[1].enabled = true;
    suite->enabled = true;
    suite->required_member_count = 1u;
    suite->optional_member_count = 1u;
    (void)snprintf(suite->required_members[0], sizeof(suite->required_members[0]),
                   "%s", "umicom.test");
    (void)snprintf(suite->optional_members[0], sizeof(suite->optional_members[0]),
                   "%s", "umicom.optional");
}

static bool load_ok(UmiPlatformArtifactCatalogue *catalogue)
{
    return umi_platform_result_is_ok(
        umi_platform_artifact_catalogue_load(CATALOGUE, catalogue));
}

static bool evaluate_ok(const UmiPlatformWorkspace *workspace,
                        const UmiPlatformSuite *suite,
                        const UmiPlatformArtifactCatalogue *catalogue,
                        UmiPlatformArtifactTarget target,
                        UmiPlatformSuiteArtifactReport *report)
{
    return umi_platform_result_is_ok(umi_platform_suite_artifacts_evaluate(
        workspace, suite, catalogue, DIRECTORY, target, report));
}

int main(void)
{
    UmiPlatformWorkspace *workspace = calloc(1u, sizeof(*workspace));
    UmiPlatformSuite *suite = calloc(1u, sizeof(*suite));
    UmiPlatformArtifactCatalogue *catalogue = calloc(1u, sizeof(*catalogue));
    UmiPlatformSuiteArtifactReport *report = calloc(1u, sizeof(*report));
    UmiPlatformResult result;
    char oversized_root[UMI_PLATFORM_PATH_MAX];
    char overlong_line[660];

    UMI_TEST_ASSERT(workspace != NULL && suite != NULL && catalogue != NULL && report != NULL);
    UMI_TEST_ASSERT(TEST_MKDIR(DIRECTORY) == 0);
    UMI_TEST_ASSERT(umi_platform_artifact_catalogue_load(NULL, catalogue).code ==
                    UMI_PLATFORM_ERROR_ARGUMENT);
    UMI_TEST_ASSERT(umi_platform_artifact_catalogue_load("missing-file", catalogue).code ==
                    UMI_PLATFORM_ERROR_IO);

    UMI_TEST_ASSERT(write_text(CATALOGUE,
        "# comment\n"
        "umicom.test umicom-test.exe umicom-test\n"
        "umicom.optional - -\n"));
    UMI_TEST_ASSERT(load_ok(catalogue));
    UMI_TEST_ASSERT(catalogue->count == 2u);
    init_workspace(workspace, suite);

    /* A mapped required image is missing; an optional - is not guessed. */
    UMI_TEST_ASSERT(evaluate_ok(workspace, suite, catalogue,
                                UMI_PLATFORM_ARTIFACT_LINUX, report));
    UMI_TEST_ASSERT(!report->ready && report->required_ready == 0u);
    UMI_TEST_ASSERT(report->members[0].state == UMI_PLATFORM_ARTIFACT_NOT_FOUND);
    UMI_TEST_ASSERT(report->members[1].state == UMI_PLATFORM_ARTIFACT_NOT_MAPPED);

    /* Present, recognised Linux image does NOT mean the program was run. */
    UMI_TEST_ASSERT(write_elf(LINUX_BIN));
    UMI_TEST_ASSERT(evaluate_ok(workspace, suite, catalogue,
                                UMI_PLATFORM_ARTIFACT_LINUX, report));
    UMI_TEST_ASSERT(report->ready && report->degraded);
    UMI_TEST_ASSERT(report->required_ready == 1u && report->optional_ready == 0u);
    UMI_TEST_ASSERT(report->members[0].state == UMI_PLATFORM_ARTIFACT_READY);

    /* Format mismatches and zero-length files must fail, not appear READY. */
    UMI_TEST_ASSERT(write_text(LINUX_BIN, "not-an-ELF"));
    UMI_TEST_ASSERT(evaluate_ok(workspace, suite, catalogue,
                                UMI_PLATFORM_ARTIFACT_LINUX, report));
    UMI_TEST_ASSERT(!report->ready &&
                    report->members[0].state == UMI_PLATFORM_ARTIFACT_BAD_IMAGE);
    UMI_TEST_ASSERT(write_elf(LINUX_BIN));

    /* A source checkout is mandatory, independently of the built image. */
    workspace->projects[0].enabled = false;
    UMI_TEST_ASSERT(evaluate_ok(workspace, suite, catalogue,
                                UMI_PLATFORM_ARTIFACT_LINUX, report));
    UMI_TEST_ASSERT(!report->ready &&
                    report->members[0].state == UMI_PLATFORM_ARTIFACT_PROJECT_UNAVAILABLE);
    workspace->projects[0].enabled = true;

    /* A disabled suite can never be READY, even with a good required image. */
    suite->enabled = false;
    UMI_TEST_ASSERT(evaluate_ok(workspace, suite, catalogue,
                                UMI_PLATFORM_ARTIFACT_LINUX, report));
    UMI_TEST_ASSERT(!report->ready);
    suite->enabled = true;

    /* All required and optional images found -> not degraded. */
    UMI_TEST_ASSERT(write_text(CATALOGUE,
        "umicom.test umicom-test.exe umicom-test\n"
        "umicom.optional umicom-test.exe umicom-test\n"));
    UMI_TEST_ASSERT(load_ok(catalogue));
    UMI_TEST_ASSERT(evaluate_ok(workspace, suite, catalogue,
                                UMI_PLATFORM_ARTIFACT_LINUX, report));
    UMI_TEST_ASSERT(report->ready && !report->degraded && report->optional_ready == 1u);

    /* A Windows PE header is recognised separately, without launching Wine. */
    UMI_TEST_ASSERT(write_pe(WINDOWS_BIN));
    UMI_TEST_ASSERT(evaluate_ok(workspace, suite, catalogue,
                                UMI_PLATFORM_ARTIFACT_WINDOWS, report));
    UMI_TEST_ASSERT(report->ready && !report->degraded);

    /* Reject an MZ decoy without a real PE/COFF signature. */
    UMI_TEST_ASSERT(write_text(WINDOWS_BIN, "MZ but not a valid PE image"));
    UMI_TEST_ASSERT(evaluate_ok(workspace, suite, catalogue,
                                UMI_PLATFORM_ARTIFACT_WINDOWS, report));
    UMI_TEST_ASSERT(!report->ready && report->members[0].state == UMI_PLATFORM_ARTIFACT_BAD_IMAGE);

    /* Malformed/duplicate/traversal inventory never replaces the good one. */
    UMI_TEST_ASSERT(write_text(CATALOGUE,
        "umicom.test umicom-test.exe umicom-test\n"
        "umicom.test another.exe another\n"));
    result = umi_platform_artifact_catalogue_load(CATALOGUE, catalogue);
    UMI_TEST_ASSERT(result.code == UMI_PLATFORM_ERROR_PARSE && catalogue->count == 2u);
    UMI_TEST_ASSERT(write_text(CATALOGUE, "umicom.test ../escape.exe good\n"));
    UMI_TEST_ASSERT(umi_platform_artifact_catalogue_load(CATALOGUE, catalogue).code ==
                    UMI_PLATFORM_ERROR_PARSE);
    UMI_TEST_ASSERT(write_text(CATALOGUE, "umicom.test valid.exe valid EXTRA\n"));
    UMI_TEST_ASSERT(umi_platform_artifact_catalogue_load(CATALOGUE, catalogue).code ==
                    UMI_PLATFORM_ERROR_PARSE);

    (void)memset(overlong_line, 'X', sizeof(overlong_line));
    overlong_line[sizeof(overlong_line) - 1u] = '\0';
    UMI_TEST_ASSERT(write_text(CATALOGUE, overlong_line));
    UMI_TEST_ASSERT(umi_platform_artifact_catalogue_load(CATALOGUE, catalogue).code ==
                    UMI_PLATFORM_ERROR_PARSE);

    /* An extremely long binary root must not overflow the output buffer. */
    UMI_TEST_ASSERT(write_text(CATALOGUE, "umicom.test umicom-test.exe umicom-test\n"));
    UMI_TEST_ASSERT(load_ok(catalogue));
    (void)memset(oversized_root, 'q', sizeof(oversized_root));
    oversized_root[sizeof(oversized_root) - 1u] = '\0';
    UMI_TEST_ASSERT(umi_platform_result_is_ok(umi_platform_suite_artifacts_evaluate(
        workspace, suite, catalogue, oversized_root,
        UMI_PLATFORM_ARTIFACT_LINUX, report)));
    UMI_TEST_ASSERT(!report->ready &&
                    report->members[0].state == UMI_PLATFORM_ARTIFACT_PATH_TOO_LONG);

    /* Unknown target and invalid suite membership must be rejected. */
    UMI_TEST_ASSERT(umi_platform_suite_artifacts_evaluate(
        workspace, suite, catalogue, DIRECTORY,
        (UmiPlatformArtifactTarget)99, report).code == UMI_PLATFORM_ERROR_ARGUMENT);
    (void)memset(suite->required_members[0], 'x', sizeof(suite->required_members[0]));
    UMI_TEST_ASSERT(umi_platform_suite_artifacts_evaluate(
        workspace, suite, catalogue, DIRECTORY,
        UMI_PLATFORM_ARTIFACT_LINUX, report).code == UMI_PLATFORM_ERROR_VALIDATION);

    UMI_TEST_ASSERT(remove(LINUX_BIN) == 0);
    UMI_TEST_ASSERT(remove(WINDOWS_BIN) == 0);
    UMI_TEST_ASSERT(remove(CATALOGUE) == 0);
    UMI_TEST_ASSERT(TEST_RMDIR(DIRECTORY) == 0);
    free(report);
    free(catalogue);
    free(suite);
    free(workspace);
    puts("PASS: suite executable artifacts, optional policy, input limits, PE/ELF recognition");
    return 0;
}
