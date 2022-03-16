include(${PROJECT_SOURCE_DIR}/CMakeModules/AddGladeHeaderTarget.cmake)

add_glade_header_target(main_window_glade
    ${CMAKE_CURRENT_SOURCE_DIR}/main_window.glade
    ${CMAKE_CURRENT_SOURCE_DIR}/main_window.glade.h.in
    MAIN_WINDOW_GLADE
    main_window.glade.h
)
add_glade_header_target(tab_general_glade
    ${CMAKE_CURRENT_SOURCE_DIR}/tab_general.glade
    ${CMAKE_CURRENT_SOURCE_DIR}/tab_general.glade.h.in
    TAB_GENERAL_GLADE
    tab_general.glade.h
)

add_executable(yuzu-sdl-config
    config.cpp
    config.h
    main.cpp
    main_window.cpp
    main_window.glade
    main_window.glade.h.in
    main_window.h
    tab_general.cpp
    tab_general.glade
    tab_general.glade.h.in
    tab_general.h
    tab.h
)

add_dependencies(yuzu-sdl-config
    main_window_glade
    tab_general_glade
)

if (NOT WIN32)
    target_link_options(yuzu-sdl-config PRIVATE "LINKER:-export-dynamic")
endif()

target_link_libraries(yuzu-sdl-config PRIVATE common)
target_include_directories(yuzu-sdl-config PRIVATE common)
target_include_directories(yuzu-sdl-config PRIVATE ${PROJECT_BINARY_DIR}/src)
target_include_directories(yuzu-sdl-config PRIVATE ${GTK3_INCLUDE_DIRS} ${GMODULE_EXPORT_INCLUDE_DIRS})
target_link_libraries(yuzu-sdl-config PRIVATE ${GTK3_LIBRARIES} ${GMODULE_EXPORT_LIBRARIES})
target_link_libraries(yuzu-sdl-config PRIVATE basicini)
