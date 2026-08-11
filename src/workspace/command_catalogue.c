/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/command_catalogue.c
 *
 * PURPOSE:
 *   Expose native workspace commands.
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

#include <umicom/platform/workspace/command_catalogue.h>
static const char *COMMANDS[]={"status","graph","sync","framework-audit","lock-plan","build-plan","test-plan","codeguard-plan","os-ui","remote-plan","migration-plan"};
size_t umi_workspace_command_count(void){return sizeof(COMMANDS)/sizeof(COMMANDS[0]);}
const char *umi_workspace_command_name(size_t i){return i<umi_workspace_command_count()?COMMANDS[i]:NULL;}
