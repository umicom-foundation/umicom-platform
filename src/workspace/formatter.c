/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/formatter.c
 *
 * PURPOSE:
 *   Format workspace status and plan output.
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
#include <umicom/platform/workspace/formatter.h>
void umi_workspace_print_heading(const char *text){printf("\n== %s ==\n",text?text:"");}
void umi_workspace_print_key_value(const char *key,const char *value){printf("%-24s %s\n",key?key:"",value?value:"");}
void umi_workspace_print_boolean(const char *key,int value){umi_workspace_print_key_value(key,value?"yes":"no");}
