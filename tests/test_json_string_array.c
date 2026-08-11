/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/test_json_string_array.c
 *
 * PURPOSE:
 *   Exercise one Batch 18 suite or Integration Fabric orchestration behaviour.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file keeps suite and integration orchestration explicit. The master
 * platform plans composition, but products remain independent repositories
 * communicating through Framework contracts rather than private state.
 */

#include <string.h>
#include <umi_test.h>
#include <umicom/platform/json.h>
int main(void) {
    char values[4][UMI_PLATFORM_ID_MAX]; size_t count=0U;
    const char *json="{\"items\":[\"alpha\",\"beta\"]}";
    UMI_TEST_ASSERT(umi_platform_json_get_string_array(json,"items",values,4U,&count));
    UMI_TEST_ASSERT(count==2U);
    UMI_TEST_ASSERT(strcmp(values[0],"alpha")==0);
    UMI_TEST_ASSERT(strcmp(values[1],"beta")==0);
    return 0;
}
