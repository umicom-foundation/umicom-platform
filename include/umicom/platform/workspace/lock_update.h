/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/workspace/lock_update.h
 *
 * PURPOSE:
 *   Plan or apply root submodule SHA updates to VERSION_LOCK without changing Gitlinks.
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
#ifndef UMICOM_PLATFORM_LOCK_UPDATE_H
#define UMICOM_PLATFORM_LOCK_UPDATE_H
#include <stdbool.h>
#include "umicom/platform/result.h"
UmiPlatformResult umi_workspace_lock_update(bool apply);
#endif
