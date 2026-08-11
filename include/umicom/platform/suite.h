/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: include/umicom/platform/suite.h
 *
 * PURPOSE:
 *   Load and classify suite manifests without coupling them to product implementations.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

/* BEGINNER NOTE:
 * This file is part of the bootstrap layer for the Umicom Platform workspace.
 * The code is intentionally small and explicit so a new developer can follow
 * how the platform discovers projects, validates files and reports problems.
 */

#ifndef UMICOM_PLATFORM_SUITE_H
#define UMICOM_PLATFORM_SUITE_H
#include <umicom/platform/result.h>
UmiPlatformResult umi_platform_suite_load(const char *path, UmiPlatformSuite *suite);
#endif
