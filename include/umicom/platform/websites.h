/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/websites.h
 *
 * PURPOSE:
 *   Represent the planned website slots without requiring unavailable Git submodules.
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

#ifndef UMICOM_PLATFORM_WEBSITES_H
#define UMICOM_PLATFORM_WEBSITES_H
void umi_platform_websites_print_status(void);
#endif
