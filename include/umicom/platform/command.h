/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/command.h
 *
 * PURPOSE:
 *   Declare the bootstrap command dispatcher used by the command-line entry point.
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

#ifndef UMICOM_PLATFORM_COMMAND_H
#define UMICOM_PLATFORM_COMMAND_H
int umi_platform_dispatch_command(int argc, char **argv);
#endif
