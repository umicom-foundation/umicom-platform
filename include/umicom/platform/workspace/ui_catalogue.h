/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/ui_catalogue.h
 *
 * PURPOSE:
 *   Expose the verified current Framework GTK4 adapter component inventory.
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

#ifndef UMICOM_PLATFORM_UI_CATALOGUE_H
#define UMICOM_PLATFORM_UI_CATALOGUE_H
#include <stddef.h>
size_t umi_ui_gtk4_current_component_count(void);
const char *umi_ui_gtk4_current_component(size_t index);
size_t umi_ui_gtk4_planned_component_count(void);
const char *umi_ui_gtk4_planned_component(size_t index);
#endif
