/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/commands/cmd_websites.c
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

#include <umicom/platform/websites.h>
int umi_cmd_websites(void) { umi_platform_websites_print_status(); return 0; }
