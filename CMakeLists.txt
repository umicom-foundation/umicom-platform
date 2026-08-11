cmake_minimum_required(VERSION 3.25)

project(UmicomPlatformBootstrap
    VERSION 0.1.0
    DESCRIPTION "Native bootstrap and validation tools for the Umicom Platform super-project"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UMICOM_PLATFORM_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)
option(UMICOM_PLATFORM_BUILD_TESTS "Build Umicom Platform bootstrap tests" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(UmicomPlatformWarnings)
include(UmicomPlatformTesting)
include(UmicomPlatformInstall)

set(UMICOM_PLATFORM_PUBLIC_HEADERS
    include/umicom/platform/command.h
    include/umicom/platform/config.h
    include/umicom/platform/diagnostic.h
    include/umicom/platform/filesystem.h
    include/umicom/platform/framework_audit.h
    include/umicom/platform/git.h
    include/umicom/platform/json.h
    include/umicom/platform/lock.h
    include/umicom/platform/manifest.h
    include/umicom/platform/path.h
    include/umicom/platform/process.h
    include/umicom/platform/project.h
    include/umicom/platform/reporter.h
    include/umicom/platform/result.h
    include/umicom/platform/string.h
    include/umicom/platform/submodule.h
    include/umicom/platform/suite.h
    include/umicom/platform/toolchain.h
    include/umicom/platform/types.h
    include/umicom/platform/validator.h
    include/umicom/platform/version.h
    include/umicom/platform/websites.h
    include/umicom/platform/workspace.h
    include/umicom/platform/workspace/workspace_command.h
    include/umicom/platform/workspace/operation.h
    include/umicom/platform/workspace/plan.h
    include/umicom/platform/workspace/sync.h
    include/umicom/platform/workspace/submodule_status.h
    include/umicom/platform/workspace/workspace_status.h
    include/umicom/platform/workspace/graph.h
    include/umicom/platform/workspace/lock_plan.h
    include/umicom/platform/workspace/build_plan.h
    include/umicom/platform/workspace/test_plan.h
    include/umicom/platform/workspace/codeguard_plan.h
    include/umicom/platform/workspace/os_ui.h
    include/umicom/platform/workspace/git_command.h
    include/umicom/platform/workspace/project_state.h
    include/umicom/platform/workspace/workspace_policy.h
    include/umicom/platform/workspace/ui_catalogue.h
    include/umicom/platform/workspace/os_layer.h
    include/umicom/platform/workspace/workspace_health.h
    include/umicom/platform/workspace/formatter.h
    include/umicom/platform/workspace/remote_plan.h
    include/umicom/platform/workspace/migration_plan.h
    include/umicom/platform/workspace/command_catalogue.h
)

set(UMICOM_PLATFORM_SOURCES
    src/base/diagnostic.c
    src/base/filesystem.c
    src/base/path.c
    src/base/process.c
    src/base/result.c
    src/base/string.c
    src/git/framework_audit.c
    src/git/git.c
    src/git/submodule.c
    src/model/lock.c
    src/model/manifest.c
    src/model/project.c
    src/model/suite.c
    src/model/workspace.c
    src/parse/json.c
    src/report/reporter.c
    src/validation/lock_validator.c
    src/validation/path_validator.c
    src/validation/project_validator.c
    src/validation/suite_validator.c
    src/validation/validator.c
    src/validation/workspace_validator.c
    src/platform/toolchain.c
    src/platform/websites.c
    src/workspace/plan.c
    src/workspace/git_command.c
    src/workspace/sync.c
    src/workspace/submodule_status.c
    src/workspace/project_state.c
    src/workspace/status.c
    src/workspace/graph.c
    src/workspace/lock_plan.c
    src/workspace/build_plan.c
    src/workspace/test_plan.c
    src/workspace/codeguard_plan.c
    src/workspace/os_layer.c
    src/workspace/ui_catalogue.c
    src/workspace/os_ui.c
    src/workspace/workspace_policy.c
    src/workspace/formatter.c
    src/workspace/remote_plan.c
    src/workspace/migration_plan.c
    src/workspace/command_catalogue.c
    src/workspace/workspace_health.c
    src/workspace/workspace_command.c
    src/commands/cmd_doctor.c
    src/commands/cmd_framework_audit.c
    src/commands/cmd_help.c
    src/commands/cmd_list.c
    src/commands/cmd_lock.c
    src/commands/cmd_project.c
    src/commands/cmd_status.c
    src/commands/cmd_suite.c
    src/commands/cmd_tree.c
    src/commands/cmd_validate.c
    src/commands/cmd_version.c
    src/commands/cmd_websites.c
)

add_library(umicom_platform_bootstrap STATIC
    ${UMICOM_PLATFORM_PUBLIC_HEADERS}
    ${UMICOM_PLATFORM_SOURCES}
)

target_include_directories(umicom_platform_bootstrap
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

umi_platform_apply_warnings(umicom_platform_bootstrap)

add_executable(umicom-platform src/main.c)
target_link_libraries(umicom-platform PRIVATE umicom_platform_bootstrap)
umi_platform_apply_warnings(umicom-platform)

set_target_properties(umicom-platform PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if(UMICOM_PLATFORM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

umi_platform_install_targets()
