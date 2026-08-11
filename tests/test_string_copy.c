/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_string_copy.c
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
int main(void){ char b[8]; UMI_TEST_ASSERT(umi_platform_string_copy(b,sizeof(b),"abc")); UMI_TEST_ASSERT(strcmp(b,"abc")==0); UMI_TEST_ASSERT(!umi_platform_string_copy(b,3u,"abcd")); return 0; }
