/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/suite_command.c
 *
 * PURPOSE:
 *   Implement native suite inspection and readiness planning without launching products yet.
 *   Implement native suite inspection and readiness planning. Keep the
 *   existing repository-level planning contract intact; expose a separate
 *   read-only executable-artifact gate without launching products.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file keeps suite and integration orchestration explicit. The master
 * platform plans composition, but products remain independent repositories
 * communicating through Framework contracts rather than private state.
 * Artifact evidence is intentionally different from source-directory
 * readiness and is never treated as proof of real process startup.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <umicom/platform/suite_runtime.h>
#include <umicom/platform/filesystem.h>
#include <umicom/platform/workspace/suite_command.h>
#include <umicom/platform/workspace/suite_artifacts.h>

#define UMI_ARTIFACT_CATALOGUE_DEFAULT "manifests/suites/executable_targets.txt"

static int load_workspace(UmiPlatformWorkspace *workspace)
{
    UmiPlatformResult result = umi_platform_workspace_load(workspace);
    if (!umi_platform_result_is_ok(result)) {
        fprintf(stderr, "%s\n", result.message);
        return 1;
    }
    return 0;
}

static void print_members(
    const char *label,
    const char members[][UMI_PLATFORM_ID_MAX],
    size_t count)
{
    size_t index;
    printf("%s (%zu):\n", label, count);
    for (index = 0U; index < count; ++index) {
        printf("  %s\n", members[index]);
    }
}

static int command_list(void)
{
    UmiPlatformWorkspace workspace;
    size_t index;
    if (load_workspace(&workspace) != 0) {
        return 1;
    }
    for (index = 0U; index < workspace.suite_count; ++index) {
        const UmiPlatformSuite *suite = &workspace.suites[index];
        printf("%-28s %-10s enabled=%s required=%zu optional=%zu\n",
               suite->id,
               suite->status,
               suite->enabled ? "yes" : "no",
               suite->required_member_count,
               suite->optional_member_count);
    }
    return 0;
}

static int command_show(const char *suite_id)
{
    UmiPlatformWorkspace workspace;
    const UmiPlatformSuite *suite;
    if (load_workspace(&workspace) != 0) {
        return 1;
    }
    suite = umi_platform_workspace_find_suite(&workspace, suite_id);
    if (suite == NULL) {
        fprintf(stderr, "suite not found: %s\n", suite_id);
        return 2;
    }
    printf("%s\n%s\nstatus=%s enabled=%s\n",
           suite->id,
           suite->name,
           suite->status,
           suite->enabled ? "yes" : "no");
    print_members("required", suite->required_members,
                  suite->required_member_count);
    print_members("optional", suite->optional_members,
                  suite->optional_member_count);
    return 0;
}

static int command_plan(const char *suite_id, bool validate_only)
{
    UmiPlatformWorkspace workspace;
    const UmiPlatformSuite *suite;
    UmiPlatformSuiteReadiness readiness;
    size_t index;
    UmiPlatformResult result;

    if (load_workspace(&workspace) != 0) {
        return 1;
    }
    suite = umi_platform_workspace_find_suite(&workspace, suite_id);
    if (suite == NULL) {
        fprintf(stderr, "suite not found: %s\n", suite_id);
        return 2;
    }

    result = umi_platform_suite_readiness(
        &workspace, suite, &readiness);
    if (!umi_platform_result_is_ok(result)) {
        fprintf(stderr, "%s\n", result.message);
        return 1;
    }

    printf("Suite: %s\n", suite->id);
    printf("Result: %s\n",
           readiness.ready
               ? (readiness.degraded ? "READY-DEGRADED" : "READY")
               : "BLOCKED");
    printf("Required: %zu/%zu available\n",
           readiness.required_available,
           readiness.required_total);
    printf("Optional: %zu/%zu available\n",
           readiness.optional_available,
           readiness.optional_total);

    if (!validate_only) {
        puts("Launch order / availability:");
        for (index = 0U; index < suite->required_member_count; ++index) {
            const UmiPlatformProject *project =
                umi_platform_workspace_find_project(
                    &workspace, suite->required_members[index]);
            printf("  REQUIRED %-30s %s\n",
                   suite->required_members[index],
                   project != NULL && project->enabled &&
                   project->path[0] != '\0' &&
                   umi_platform_path_exists(project->path)
                       ? "READY" : "MISSING");
        }
        for (index = 0U; index < suite->optional_member_count; ++index) {
            const UmiPlatformProject *project =
                umi_platform_workspace_find_project(
                    &workspace, suite->optional_members[index]);
            printf("  OPTIONAL %-30s %s\n",
                   suite->optional_members[index],
                   project != NULL && project->enabled &&
                   project->path[0] != '\0' &&
                   umi_platform_path_exists(project->path)
                       ? "READY" : "SKIP");
        }
    }

    return readiness.ready ? 0 : 2;
}

static void print_artifact_usage(void)
{
    fputs("usage: workspace suite artifacts SUITE-ID --bin-dir DIRECTORY "
          "[--catalogue FILE] [--target windows|linux]\n", stderr);
}

/* A distinct command: the earlier plan/validate flags continue reporting
 * manifest/source readiness as before; their callers are not reinterpreted. */
static int command_artifacts(int argc, char **argv)
{
    const char *bin_dir = NULL;
    const char *catalogue_path = UMI_ARTIFACT_CATALOGUE_DEFAULT;
    UmiPlatformArtifactTarget target;
    UmiPlatformWorkspace *workspace = NULL;
    UmiPlatformArtifactCatalogue *catalogue = NULL;
    UmiPlatformSuiteArtifactReport *report = NULL;
    const UmiPlatformSuite *suite;
    UmiPlatformResult result;
    int i;
    int exit_code = 2;
    size_t index;
    bool catalogue_specified = false;
    bool target_specified = false;

#ifdef _WIN32
    target = UMI_PLATFORM_ARTIFACT_WINDOWS;
#else
    target = UMI_PLATFORM_ARTIFACT_LINUX;
#endif
    if (argc < 3 || argv == NULL || argv[0] == NULL) {
        print_artifact_usage();
        return 2;
    }
    for (i = 1; i < argc; i += 2) {
        if (i + 1 >= argc || argv[i + 1] == NULL || argv[i + 1][0] == '\0') {
            print_artifact_usage();
            return 2;
        }
        if (strcmp(argv[i], "--bin-dir") == 0 && bin_dir == NULL) {
            bin_dir = argv[i + 1];
        } else if (strcmp(argv[i], "--catalogue") == 0 && !catalogue_specified) {
            catalogue_path = argv[i + 1];
            catalogue_specified = true;
        } else if (strcmp(argv[i], "--target") == 0 && !target_specified) {
            target_specified = true;
            if (strcmp(argv[i + 1], "windows") == 0) {
                target = UMI_PLATFORM_ARTIFACT_WINDOWS;
            } else if (strcmp(argv[i + 1], "linux") == 0) {
                target = UMI_PLATFORM_ARTIFACT_LINUX;
            } else {
                print_artifact_usage();
                return 2;
            }
        } else {
            print_artifact_usage();
            return 2;
        }
    }
    if (bin_dir == NULL || !umi_platform_directory_exists(bin_dir)) {
        fprintf(stderr, "binary directory not found: %s\n",
                bin_dir == NULL ? "(not provided)" : bin_dir);
        return 2;
    }

    /* A complete Platform workspace and artifact report may exceed Windows'
     * default thread stack if allocated together as local variables. These
     * bounded records are owned here and released on every exit path. */
    workspace = calloc(1u, sizeof(*workspace));
    catalogue = calloc(1u, sizeof(*catalogue));
    report = calloc(1u, sizeof(*report));
    if (workspace == NULL || catalogue == NULL || report == NULL) {
        fputs("cannot allocate suite artifact evaluation state\n", stderr);
        goto cleanup;
    }
    if (load_workspace(workspace) != 0) {
        exit_code = 1;
        goto cleanup;
    }
    suite = umi_platform_workspace_find_suite(workspace, argv[0]);
    if (suite == NULL) {
        fprintf(stderr, "suite not found: %s\n", argv[0]);
        goto cleanup;
    }
    result = umi_platform_artifact_catalogue_load(catalogue_path, catalogue);
    if (!umi_platform_result_is_ok(result)) {
        fprintf(stderr, "catalogue: %s (%s)\n", result.message, catalogue_path);
        goto cleanup;
    }
    result = umi_platform_suite_artifacts_evaluate(
        workspace, suite, catalogue, bin_dir, target, report);
    if (!umi_platform_result_is_ok(result)) {
        fprintf(stderr, "%s\n", result.message);
        goto cleanup;
    }
    printf("Suite: %s\nTarget: %s\nBinary directory: %s\n",
           suite->id, target == UMI_PLATFORM_ARTIFACT_WINDOWS ? "windows" : "linux", bin_dir);
    printf("Artifact result: %s\n",
           report->ready ? (report->degraded ? "READY-DEGRADED" : "READY-IMAGES") : "BLOCKED");
    printf("Required images: %zu/%zu\nOptional images: %zu/%zu\n",
           report->required_ready, report->required_total,
           report->optional_ready, report->optional_total);
    for (index = 0u; index < report->member_count; ++index) {
        const UmiPlatformArtifactMember *member = &report->members[index];
        printf("  %-8s %-30s %-24s %s\n",
               member->required ? "REQUIRED" : "OPTIONAL",
               member->project_id,
               umi_platform_artifact_state_text(member->state),
               member->artifact_path[0] != '\0' ? member->artifact_path : "(no mapped image)");
    }
    puts("NOTE: This checks local artifact structure only. It does not launch, sign, authenticate or test applications.");
    exit_code = report->ready ? 0 : 2;
cleanup:
    free(report);
    free(catalogue);
    free(workspace);
    return exit_code;
}

int umi_workspace_suite_command(int argc, char **argv)
{
    if (argc < 1) {
        /* The expanded help below includes the artifact inspection command.
         * Keep the earlier help text for review without hiding the new action. */
#if 0
        puts("usage: workspace suite list|show|plan|validate [suite-id]");
#endif
        puts("usage: workspace suite list|show|plan|validate|artifacts [suite-id]");
        return 0;
    }
    if (strcmp(argv[0], "list") == 0) {
        return command_list();
    }
    if (argc < 2) {
        fputs("suite id is required\n", stderr);
        return 2;
    }
    if (strcmp(argv[0], "show") == 0) {
        return command_show(argv[1]);
    }
    if (strcmp(argv[0], "plan") == 0) {
        return command_plan(argv[1], false);
    }
    if (strcmp(argv[0], "validate") == 0) {
        return command_plan(argv[1], true);
    }
    if (strcmp(argv[0], "artifacts") == 0) {
        return command_artifacts(argc - 1, argv + 1);
    }
    fprintf(stderr, "unknown suite command: %s\n", argv[0]);
    return 2;
}
