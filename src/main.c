/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/main.c
 *
 * PURPOSE:
 *   Dispatch native bootstrap commands.
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
int umi_cmd_doctor(void);
int umi_cmd_framework_audit(void);
int umi_cmd_help(void);
int umi_cmd_list(void);
int umi_cmd_lock(void);
int umi_cmd_project(const char *id);
int umi_cmd_status(void);
int umi_cmd_suite(void);
int umi_cmd_tree(void);
int umi_cmd_validate(void);
int umi_cmd_version(void);
int umi_cmd_websites(void);
int umi_platform_workspace_command(int argc, char **argv);

int main(int argc, char **argv) {
    if (argc < 2) return umi_cmd_help();
    const char *cmd = argv[1];
    if (strcmp(cmd, "doctor") == 0) return umi_cmd_doctor();
    if (strcmp(cmd, "framework-audit") == 0) return umi_cmd_framework_audit();
    if (strcmp(cmd, "help") == 0 || strcmp(cmd, "--help") == 0) return umi_cmd_help();
    if (strcmp(cmd, "list") == 0) return umi_cmd_list();
    if (strcmp(cmd, "lock") == 0) return umi_cmd_lock();
    if (strcmp(cmd, "project") == 0) return umi_cmd_project(argc >= 3 ? argv[2] : NULL);
    if (strcmp(cmd, "status") == 0) return umi_cmd_status();
    if (strcmp(cmd, "suite") == 0) return umi_cmd_suite();
    if (strcmp(cmd, "tree") == 0) return umi_cmd_tree();
    if (strcmp(cmd, "validate") == 0) return umi_cmd_validate();
    if (strcmp(cmd, "version") == 0 || strcmp(cmd, "--version") == 0) return umi_cmd_version();
    if (strcmp(cmd, "websites") == 0) return umi_cmd_websites();
    if (strcmp(cmd, "workspace") == 0) return umi_platform_workspace_command(argc - 2, argv + 2);
    fprintf(stderr, "unknown command: %s\n", cmd);
    return 2;
}
