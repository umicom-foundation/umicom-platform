/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/os_layer.h
 *
 * PURPOSE:
 *   Represent the separation between Linux base layers and Framework-dependent Umicom user-space.
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

#ifndef UMICOM_PLATFORM_OS_LAYER_H
#define UMICOM_PLATFORM_OS_LAYER_H
#include <stdbool.h>
typedef enum UmiOsLayer {
    UMI_OS_LAYER_KERNEL,
    UMI_OS_LAYER_BASE_USERLAND,
    UMI_OS_LAYER_FRAMEWORK_RUNTIME,
    UMI_OS_LAYER_DESKTOP_SHELL,
    UMI_OS_LAYER_APPLICATION
} UmiOsLayer;
bool umi_os_layer_depends_on_framework(UmiOsLayer layer);
const char *umi_os_layer_name(UmiOsLayer layer);
#endif
