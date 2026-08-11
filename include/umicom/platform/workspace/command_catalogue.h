/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/command_catalogue.h
 *
 * PURPOSE:
 *   Expose the current nested workspace command catalogue.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file implements one small part of the native Umicom Platform workspace
 * orchestrator. The logic stays explicit so new developers can follow how the
 * super-project plans and validates recursive Git, build and release actions.
 */

#ifndef UMICOM_PLATFORM_COMMAND_CATALOGUE_H
#define UMICOM_PLATFORM_COMMAND_CATALOGUE_H
#include <stddef.h>
size_t umi_workspace_command_count(void);
const char *umi_workspace_command_name(size_t index);
#endif
