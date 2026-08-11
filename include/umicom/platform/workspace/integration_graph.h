/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/integration_graph.h
 *
 * PURPOSE:
 *   Print a suite-centred public integration graph from platform manifests.
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

#ifndef UMICOM_PLATFORM_WORKSPACE_INTEGRATION_GRAPH_H
#define UMICOM_PLATFORM_WORKSPACE_INTEGRATION_GRAPH_H
#include <umicom/platform/result.h>
UmiPlatformResult umi_workspace_print_integration_graph(void);
#endif
