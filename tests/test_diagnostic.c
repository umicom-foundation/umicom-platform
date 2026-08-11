/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_diagnostic.c
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
#include <umicom/platform/diagnostic.h>
int main(void){ UMI_TEST_ASSERT(strcmp(umi_platform_severity_name(UMI_PLATFORM_SEVERITY_WARNING),"warning")==0); return 0; }
