/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/graph.h
 *
 * PURPOSE:
 *   Build a simple dependency graph showing Framework as the common product foundation.
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

#ifndef UMICOM_PLATFORM_GRAPH_H
#define UMICOM_PLATFORM_GRAPH_H
#include <umicom/platform/result.h>
UmiPlatformResult umi_workspace_print_graph(void);
#endif
