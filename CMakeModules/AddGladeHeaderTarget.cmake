function(add_glade_header_target _TARGET GLADE_FILE HEADER_IN_FILE REPLACE_VAR RESULT_HEADER)
    configure_file(${PROJECT_SOURCE_DIR}/CMakeModules/GenerateHeaderFromGlade.cmake.in
                   ${CMAKE_CURRENT_BINARY_DIR}/GenerateHeaderFromGlade.${_TARGET}.cmake @ONLY)

    add_custom_command(
        OUTPUT
            ${RESULT_HEADER}
        COMMAND
            ${CMAKE_COMMAND}
                -P ${CMAKE_CURRENT_BINARY_DIR}/GenerateHeaderFromGlade.${_TARGET}.cmake
        MAIN_DEPENDENCY
            ${GLADE_FILE}
    )

    add_custom_target(${_TARGET}
        DEPENDS
            ${RESULT_HEADER}
    )
endfunction()
