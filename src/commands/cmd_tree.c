/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/commands/cmd_tree.c
 *
 * PURPOSE:
 *   Implement one native Umicom Platform bootstrap command.
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
#include <umicom/platform/workspace.h>
int umi_cmd_tree(void) {
    UmiPlatformWorkspace w;
    UmiPlatformResult r = umi_platform_workspace_load(&w);
    if (!umi_platform_result_is_ok(r)) { fprintf(stderr, "%s\n", r.message); return 1; }
    puts("umicom-platform");
    puts("|-- framework");
    puts("|-- applications");
    puts("|-- services");
    puts("|-- websites");
    puts("|-- operating-systems");
    puts("`-- suites");
    return 0;
}
