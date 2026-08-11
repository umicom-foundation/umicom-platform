/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/lock_edit.c
 *
 * PURPOSE:
 *   Replace one 40-character Git SHA in the projects section of VERSION_LOCK JSON.
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
#include "umicom/platform/workspace/lock_edit.h"
#include <stdio.h>
#include <string.h>
bool umi_workspace_lock_replace_sha(char*j,size_t cap,const char*k,const char*sha){if(!j||!k||!sha||strlen(sha)!=40U)return false;char needle[128];int n=snprintf(needle,sizeof(needle),"\"%s\": \"",k);if(n<0||(size_t)n>=sizeof(needle))return false;char*p=strstr(j,needle);if(!p)return false;p+=strlen(needle);if((size_t)(p-j)+40U>=cap)return false;if(p[40]!='\"')return false;memcpy(p,sha,40U);return true;}
