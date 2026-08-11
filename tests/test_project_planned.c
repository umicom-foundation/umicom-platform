/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_project_planned.c
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
#include <umicom/platform/project.h>
int main(void){ UmiPlatformProject p={0}; strcpy(p.status,"planned"); UMI_TEST_ASSERT(umi_platform_project_is_planned(&p)); return 0; }
