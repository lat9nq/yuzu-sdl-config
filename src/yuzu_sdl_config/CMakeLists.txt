add_executable(yuzu-sdl-config
    config.cpp
    config.h
    main.cpp
    main_window.cpp
    main_window.glade
    main_window.h
    tab/debug.cpp
    tab/debug.glade
    tab/debug.h
    tab/debug_cpu.cpp
    tab/debug_cpu.glade
    tab/debug_cpu.h
    tab/general.cpp
    tab/general.glade
    tab/general.h
    tab/network.cpp
    tab/network.glade
    tab/network.h
    tab/system.cpp
    tab/system.glade
    tab/system.h
    tab/tab.h
    tab/web_service.cpp
    tab/web_service.glade
    tab/web_service.h
)

set(GLADE_FILES
    main_window.glade
    tab/debug.glade
    tab/debug_cpu.glade
    tab/general.glade
    tab/network.glade
    tab/system.glade
    tab/web_service.glade
)

set(GLADE_HEADER_GENERATOR ${PROJECT_SOURCE_DIR}/CMakeModules/GenerateHeaderFromGlade.cmake)
set(GLADE_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/tab/glade.h.in)

foreach(GLADE_FILE ${GLADE_FILES})
    get_filename_component(TAB_NAME ${GLADE_FILE} NAME_WE)
    set(TAB_NAME ${TAB_NAME}_glade)
    set(GLADE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/${GLADE_FILE})
    set(GLADE_HEADER ${CMAKE_CURRENT_BINARY_DIR}/${GLADE_FILE}.h)
    add_custom_command(
        OUTPUT
            ${GLADE_HEADER}
        COMMAND
            ${CMAKE_COMMAND} -P ${GLADE_HEADER_GENERATOR} ${GLADE_SOURCE} ${GLADE_HEADER} ${TAB_NAME} ${GLADE_TEMPLATE}
        MAIN_DEPENDENCY
            ${GLADE_SOURCE}
        DEPENDS
            ${GLADE_HEADER_GENERATOR}
            ${GLADE_TEMPLATE}
    )
    list(APPEND GLADE_HEADERS ${GLADE_HEADER})
endforeach()

add_custom_target(glade_headers
DEPENDS
    ${GLADE_HEADERS}
SOURCES
    ${GLADE_FILES}
)
unset(GLADE_HEADERS)

target_link_libraries(yuzu-sdl-config INTERFACE glade_headers)

if (NOT WIN32)
    target_link_options(yuzu-sdl-config PRIVATE "LINKER:-export-dynamic")
endif()

target_include_directories(yuzu-sdl-config PRIVATE ${PROJECT_SOURCE_DIR}/externals/yuzu/src)
target_include_directories(yuzu-sdl-config PRIVATE ${PROJECT_BINARY_DIR}/src)
target_include_directories(yuzu-sdl-config PRIVATE ${GTK3_INCLUDE_DIRS} ${GMODULE_EXPORT_INCLUDE_DIRS})
target_link_libraries(yuzu-sdl-config PRIVATE ${GTK3_LIBRARIES} ${GMODULE_EXPORT_LIBRARIES})
target_link_libraries(yuzu-sdl-config PRIVATE basicini)
