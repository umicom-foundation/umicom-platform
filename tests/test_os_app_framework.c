/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_os_app_framework.c
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
#include <umi_test.h>
#include <umicom/platform/workspace/os_layer.h>
int main(void){UMI_TEST_ASSERT(umi_os_layer_depends_on_framework(UMI_OS_LAYER_APPLICATION));return 0;}
