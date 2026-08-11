/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_lock.c
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
#include <umicom/platform/lock.h>
int main(void){ char sha[UMI_PLATFORM_SHA_MAX]; UmiPlatformResult r=umi_platform_lock_framework_sha(sha,sizeof(sha)); UMI_TEST_ASSERT(umi_platform_result_is_ok(r)); UMI_TEST_ASSERT(strlen(sha)==40u); return 0; }
