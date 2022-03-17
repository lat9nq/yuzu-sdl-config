include(${PROJECT_SOURCE_DIR}/CMakeModules/AddGladeHeaderTarget.cmake)

add_glade_header_target(main_window_glade
    ${CMAKE_CURRENT_SOURCE_DIR}/main_window.glade
    ${CMAKE_CURRENT_SOURCE_DIR}/main_window.glade.h.in
    MAIN_WINDOW_GLADE
    main_window.glade.h
)
add_glade_header_target(tab_general_glade
    ${CMAKE_CURRENT_SOURCE_DIR}/tab/general.glade
    ${CMAKE_CURRENT_SOURCE_DIR}/tab/general.glade.h.in
    TAB_GENERAL_GLADE
    tab/general.glade.h
)
add_glade_header_target(tab_debug_glade
    ${CMAKE_CURRENT_SOURCE_DIR}/tab/debug.glade
    ${CMAKE_CURRENT_SOURCE_DIR}/tab/debug.glade.h.in
    TAB_DEBUG_GLADE
    tab/debug.glade.h
)
add_glade_header_target(tab_web_service_glade
    ${CMAKE_CURRENT_SOURCE_DIR}/tab/web_service.glade
    ${CMAKE_CURRENT_SOURCE_DIR}/tab/web_service.glade.h.in
    TAB_WEB_SERVICE_GLADE
    tab/web_service.glade.h
)

add_executable(yuzu-sdl-config
    config.cpp
    config.h
    main.cpp
    main_window.cpp
    main_window.glade
    main_window.glade.h.in
    main_window.h
    tab/tab.h
    tab/debug.cpp
    tab/debug.glade
    tab/debug.glade.h.in
    tab/debug.h
    tab/general.cpp
    tab/general.glade
    tab/general.glade.h.in
    tab/general.h
    tab/web_service.cpp
    tab/web_service.glade
    tab/web_service.glade.h.in
    tab/web_service.h
)

add_dependencies(yuzu-sdl-config
    main_window_glade
    tab_general_glade
    tab_debug_glade
    tab_web_service_glade
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
