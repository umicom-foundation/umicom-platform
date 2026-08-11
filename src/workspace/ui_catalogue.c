/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/ui_catalogue.c
 *
 * PURPOSE:
 *   Expose current and planned reusable GTK4 components.
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

#include <umicom/platform/workspace/ui_catalogue.h>
static const char *CURRENT[]={"gtk4_adapter","application_shell","workbench","pane","editor","menu","toolbar","status","notification","theme","accessibility","selection","dialog","clipboard","declarative_renderer"};
static const char *PLANNED[]={"window","header_bar","button","label","entry","text_view","source_view","list_view","tree_view","column_view","tab_host","paned","scrolled_view","popover","context_menu","command_palette","search_bar","property_editor","settings_page","progress","spinner","error_state","file_chooser","folder_chooser","chart_surface","media_host","browser_host"};
size_t umi_ui_gtk4_current_component_count(void){return sizeof(CURRENT)/sizeof(CURRENT[0]);}
const char *umi_ui_gtk4_current_component(size_t i){return i<umi_ui_gtk4_current_component_count()?CURRENT[i]:NULL;}
size_t umi_ui_gtk4_planned_component_count(void){return sizeof(PLANNED)/sizeof(PLANNED[0]);}
const char *umi_ui_gtk4_planned_component(size_t i){return i<umi_ui_gtk4_planned_component_count()?PLANNED[i]:NULL;}
