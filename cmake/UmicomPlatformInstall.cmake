include(GNUInstallDirs)
function(umi_platform_install_targets)
    install(TARGETS umicom_platform_bootstrap umicom-platform
        EXPORT UmicomPlatformBootstrapTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )
endfunction()
