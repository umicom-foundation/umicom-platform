/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/project_state.c
 *
 * PURPOSE:
 *   Read one local project's filesystem and Git state.
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

#include <string.h>
#include <umicom/platform/filesystem.h>
#include <umicom/platform/git.h>
#include <umicom/platform/workspace/project_state.h>
bool umi_project_state_read(const UmiPlatformProject *project,UmiProjectState *state){
    if(project==NULL||state==NULL) return false;
    memset(state,0,sizeof(*state));
    state->project=*project;
    state->path_exists=umi_platform_path_exists(project->path);
    if(state->path_exists){
        state->head_available=umi_platform_git_head(project->path,state->head,sizeof(state->head));
        state->git_repository=state->head_available;
    }
    return true;
}
