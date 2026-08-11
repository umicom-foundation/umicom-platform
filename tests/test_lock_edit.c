/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_lock_edit.c
 *
 * PURPOSE:
 *   Test safe VERSION_LOCK SHA replacement.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file keeps one responsibility small and explicit. Read the public
 * structure/function declarations first, then follow the implementation in
 * the matching source file.
 */
#include <string.h>
#include <umi_test.h>
#include <umicom/platform/workspace/lock_edit.h>
int main(void)
{
    char json[256] = "{\"framework\": \"1111111111111111111111111111111111111111\"}";
    const char *sha = "2222222222222222222222222222222222222222";
    UMI_TEST_ASSERT(umi_workspace_lock_replace_sha(json, sizeof(json), "framework", sha));
    UMI_TEST_ASSERT(strstr(json, sha) != NULL);
    return 0;
}
