/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_json_string.c
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
#include <string.h>
#include <umi_test.h>
#include <umicom/platform/json.h>
int main(void){ char b[32]; UMI_TEST_ASSERT(umi_platform_json_get_string("{\"id\":\"umicom.test\"}","id",b,sizeof(b))); UMI_TEST_ASSERT(strcmp(b,"umicom.test")==0); return 0; }
