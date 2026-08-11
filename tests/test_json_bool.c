/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_json_bool.c
 *
 * PURPOSE:
 *   Exercise one bounded platform bootstrap behaviour.
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
#include <umi_test.h>
#include <umicom/platform/json.h>
int main(void){ bool v=false; UMI_TEST_ASSERT(umi_platform_json_get_bool("{\"enabled\":true}","enabled",&v)); UMI_TEST_ASSERT(v); return 0; }
