/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_string_trim.c
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
#include <umicom/platform/string.h>
int main(void){ char b[]="  abc \r\n"; umi_platform_string_trim(b); UMI_TEST_ASSERT(strcmp(b,"abc")==0); return 0; }
