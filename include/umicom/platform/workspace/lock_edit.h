/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/lock_edit.h
 *
 * PURPOSE:
 *   Replace a fixed-length SHA value for one known project key in the in-memory lock JSON.
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
#ifndef UMICOM_PLATFORM_LOCK_EDIT_H
#define UMICOM_PLATFORM_LOCK_EDIT_H
#include <stdbool.h>
#include <stddef.h>
bool umi_workspace_lock_replace_sha(char *json,size_t capacity,const char *key,const char *sha);
#endif
