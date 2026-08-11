/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/validation/suite_validator.c
 *
 * PURPOSE:
 *   Validate suite manifest fields.
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

#include <umicom/platform/suite.h>
bool umi_platform_validation_suite_fields(const UmiPlatformSuite *suite) {
    return suite != NULL && suite->id[0] != '\0' && suite->name[0] != '\0' && suite->status[0] != '\0';
}
