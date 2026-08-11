/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/platform/websites.c
 *
 * PURPOSE:
 *   Report planned website slots without fake submodule URLs.
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
#include <umicom/platform/websites.h>
void umi_platform_websites_print_status(void) {
    puts("Umicom Foundation Website : planned / submodule not configured");
    puts("Umicom Framework Website  : planned / submodule not configured");
    puts("No placeholder URL should be entered into PowerShell.");
}
