/*-----------------------------------------------------------------------------
 * Umicom Platform
 * File: src/workspace/lock_update.c
 *
 * PURPOSE:
 *   Read active project HEADs and optionally update their SHA fields in VERSION_LOCK.
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
#include "umicom/platform/workspace/lock_update.h"
#include "umicom/platform/workspace/lock_edit.h"
#include "umicom/platform/workspace/project_state.h"
#include "umicom/platform/git.h"
#include "umicom/platform/workspace.h"
#include "umicom/platform/filesystem.h"
#include <stdio.h>
#include <string.h>
static const char *key_from_id(const char *id){return id&&strncmp(id,"umicom.",7U)==0?id+7:id;}
UmiPlatformResult umi_workspace_lock_update(bool apply){char json[32768];size_t len=0;if(!umi_platform_read_text_file("VERSION_LOCK.json",json,sizeof(json),&len))return umi_platform_result_error(UMI_PLATFORM_ERROR_IO,"cannot read VERSION_LOCK.json");UmiPlatformWorkspace w;UmiPlatformResult r=umi_platform_workspace_load(&w);if(!umi_platform_result_is_ok(r))return r;puts(apply?"Applying VERSION_LOCK project SHAs:":"VERSION_LOCK update plan:");for(size_t i=0;i<w.project_count;++i){const UmiPlatformProject*p=&w.projects[i];if(!p->enabled)continue;UmiProjectState s;if(!umi_project_state_read(p,&s)||!s.head_available)continue;const char*key=key_from_id(p->id);printf("  %-24s %s\n",key,s.head);if(apply)(void)umi_workspace_lock_replace_sha(json,sizeof(json),key,s.head);}if(apply){
        char sha[UMI_PLATFORM_SHA_MAX];
        if(umi_platform_git_head("framework",sha,sizeof(sha))) (void)umi_workspace_lock_replace_sha(json,sizeof(json),"studio-framework",sha);
        if(umi_platform_git_head("services/authorengine",sha,sizeof(sha))) (void)umi_workspace_lock_replace_sha(json,sizeof(json),"studio-authorengine",sha);
        if(umi_platform_git_head("services/authorengine/third_party/llama.cpp",sha,sizeof(sha))) (void)umi_workspace_lock_replace_sha(json,sizeof(json),"authorengine-llama.cpp",sha);
        FILE*f=fopen("VERSION_LOCK.json","wb");if(!f)return umi_platform_result_error(UMI_PLATFORM_ERROR_IO,"cannot write VERSION_LOCK.json");if(fwrite(json,1U,strlen(json),f)!=strlen(json)){fclose(f);return umi_platform_result_error(UMI_PLATFORM_ERROR_IO,"cannot write complete VERSION_LOCK.json");}fclose(f);}
    return umi_platform_result_ok();
}
