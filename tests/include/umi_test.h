/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: tests/include/umi_test.h
 *
 * PURPOSE:
 *   Provide a tiny assertion helper for bootstrap unit tests.
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

#ifndef UMI_PLATFORM_TEST_H
#define UMI_PLATFORM_TEST_H
#include <stdio.h>
#define UMI_TEST_ASSERT(expr) do { if (!(expr)) { fprintf(stderr, "FAILED: %s:%d: %s\n", __FILE__, __LINE__, #expr); return 1; } } while (0)
#endif
