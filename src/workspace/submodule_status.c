/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/submodule_status.c
 *
 * PURPOSE:
 *   Parse recursive Git submodule status output.
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
#include <string.h>
#include <umicom/platform/string.h>
#include <umicom/platform/workspace/git_command.h>
#include <umicom/platform/workspace/submodule_status.h>
const char *umi_submodule_state_name(UmiSubmoduleState state){
    switch(state){
        case UMI_SUBMODULE_INITIALIZED:return "initialized";
        case UMI_SUBMODULE_NOT_INITIALIZED:return "not-initialized";
        case UMI_SUBMODULE_DIFFERENT_COMMIT:return "different-commit";
        case UMI_SUBMODULE_CONFLICT:return "conflict";
        default:return "unknown";
    }
}
bool umi_submodule_status_parse_line(const char *line,UmiSubmoduleRecord *record){
    if(line==NULL||record==NULL||line[0]=='\0') return false;
    memset(record,0,sizeof(*record));
    const char prefix=line[0];
    record->state=prefix=='-'?UMI_SUBMODULE_NOT_INITIALIZED:prefix=='+'?UMI_SUBMODULE_DIFFERENT_COMMIT:prefix=='U'?UMI_SUBMODULE_CONFLICT:UMI_SUBMODULE_INITIALIZED;
    const char *sha=line+1;
    if(strlen(sha)<41u) return false;
    memcpy(record->sha,sha,40u); record->sha[40]='\0';
    const char *path=sha+41;
    while(*path==' ') ++path;
    const char *end=strchr(path,' ');
    size_t len=end?(size_t)(end-path):strcspn(path,"\r\n");
    if(len==0u||len>=sizeof(record->path)) return false;
    memcpy(record->path,path,len); record->path[len]='\0';
    return true;
}
bool umi_submodule_status_snapshot(UmiSubmoduleSnapshot *snapshot){
    if(snapshot==NULL) return false;
    memset(snapshot,0,sizeof(*snapshot));
    char output[65536]; int code=-1;
    if(!umi_git_command_capture("submodule status --recursive",output,sizeof(output),&code)||code!=0) return false;
    char *cursor=output;
    while(*cursor!='\0' && snapshot->count<UMI_WORKSPACE_MAX_SUBMODULES){
        char *newline=strchr(cursor,'\n');
        if(newline!=NULL) *newline='\0';
        UmiSubmoduleRecord r;
        if(umi_submodule_status_parse_line(cursor,&r)) snapshot->records[snapshot->count++]=r;
        if(newline==NULL) break;
        cursor=newline+1;
    }
    return true;
}
