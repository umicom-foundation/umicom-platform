/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/commands/cmd_list.c
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
int umi_cmd_list(void) {
    UmiPlatformWorkspace w;
    UmiPlatformResult r = umi_platform_workspace_load(&w);
    if (!umi_platform_result_is_ok(r)) { fprintf(stderr, "%s\n", r.message); return 1; }
    for (size_t i = 0u; i < w.project_count; ++i) printf("%s\n", w.projects[i].id);
    return 0;
}
