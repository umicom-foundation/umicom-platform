/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/os_ui.c
 *
 * PURPOSE:
 *   Print the Umicom OS and GTK4 reuse decision.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file implements one small part of the native Umicom Platform workspace
 * orchestrator. The logic stays explicit so new developers can follow how the
 * super-project plans and validates recursive Git, build and release actions.
 */

#include <stdio.h>
#include <umicom/platform/workspace/os_layer.h>
#include <umicom/platform/workspace/ui_catalogue.h>
#include <umicom/platform/workspace/os_ui.h>
void umi_workspace_print_os_ui_policy(void){
    puts("Umicom OS Framework dependency:");
    for(int i=(int)UMI_OS_LAYER_KERNEL;i<=(int)UMI_OS_LAYER_APPLICATION;++i){
        UmiOsLayer layer=(UmiOsLayer)i;
        printf("  %-20s framework=%s\n",umi_os_layer_name(layer),umi_os_layer_depends_on_framework(layer)?"yes":"no");
    }
    puts("Framework GTK4 current reusable implementations:");
    for(size_t i=0u;i<umi_ui_gtk4_current_component_count();++i) printf("  %s\n",umi_ui_gtk4_current_component(i));
    printf("Planned reusable GTK4 component families: %zu\n",umi_ui_gtk4_planned_component_count());
}
