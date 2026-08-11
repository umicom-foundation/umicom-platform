/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/os_layer.c
 *
 * PURPOSE:
 *   Encode which Umicom OS layers depend on Framework.
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

#include <umicom/platform/workspace/os_layer.h>
bool umi_os_layer_depends_on_framework(UmiOsLayer layer){
    return layer==UMI_OS_LAYER_FRAMEWORK_RUNTIME||layer==UMI_OS_LAYER_DESKTOP_SHELL||layer==UMI_OS_LAYER_APPLICATION;
}
const char *umi_os_layer_name(UmiOsLayer layer){
    switch(layer){
        case UMI_OS_LAYER_KERNEL:return "linux-kernel";
        case UMI_OS_LAYER_BASE_USERLAND:return "base-userland";
        case UMI_OS_LAYER_FRAMEWORK_RUNTIME:return "framework-runtime";
        case UMI_OS_LAYER_DESKTOP_SHELL:return "desktop-shell";
        case UMI_OS_LAYER_APPLICATION:return "application";
        default:return "unknown";
    }
}
