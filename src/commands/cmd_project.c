/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/commands/cmd_project.c
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
#include <string.h>
#include <umicom/platform/workspace.h>
int umi_cmd_project(const char *id) {
    if (id == NULL) { fputs("project id required\n", stderr); return 2; }
    UmiPlatformWorkspace w;
    UmiPlatformResult r = umi_platform_workspace_load(&w);
    if (!umi_platform_result_is_ok(r)) { fprintf(stderr, "%s\n", r.message); return 1; }
    for (size_t i = 0u; i < w.project_count; ++i) {
        const UmiPlatformProject *p = &w.projects[i];
        if (strcmp(p->id, id) == 0) {
            printf("id=%s\nname=%s\ntype=%s\npath=%s\nrepository=%s\nstatus=%s\nenabled=%s\n",
                   p->id, p->name, p->type, p->path, p->repository, p->status, p->enabled ? "true" : "false");
            return 0;
        }
    }
    fputs("project not found\n", stderr);
    return 3;
}
