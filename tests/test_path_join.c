/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_path_join.c
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
#include <umicom/platform/path.h>
int main(void){ char b[128]; UMI_TEST_ASSERT(umi_platform_path_join(b,sizeof(b),"applications","tms")); UMI_TEST_ASSERT(strstr(b,"applications")!=NULL); UMI_TEST_ASSERT(strstr(b,"tms")!=NULL); return 0; }
