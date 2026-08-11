/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/commands/cmd_help.c
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
int umi_cmd_help(void) {
    puts("Umicom Platform bootstrap tool");
    puts("Commands:");
    puts("  doctor             check bootstrap tools");
    puts("  status             list project state");
    puts("  validate           validate manifests and required paths");
    puts("  framework-audit    compare nested Framework revisions");
    puts("  list               list project IDs");
    puts("  tree               show platform categories");
    puts("  lock               show locked Framework SHA");
    puts("  websites           show planned website status");
    puts("  suite              list suites");
    puts("  project <id>       show one project");
    puts("  version            show bootstrap version");
    puts("  workspace <command> native recursive workspace orchestration");
    return 0;
}
