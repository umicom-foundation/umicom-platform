/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_gtk_current_shell.c
 *
 * PURPOSE:
 *   Exercise one Batch 16 workspace orchestration or OS/UI architecture behaviour.
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
#include <string.h>
#include <umi_test.h>
#include <umicom/platform/workspace/ui_catalogue.h>
int main(void){UMI_TEST_ASSERT(strcmp(umi_ui_gtk4_current_component(1u),"application_shell")==0);return 0;}
