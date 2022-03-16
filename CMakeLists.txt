cmake_minimum_required(VERSION 3.13)
project(yuzu-sdl-config)

# Output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include(FindPkgConfig)
if (NOT PKG_CONFIG_FOUND)
    message(FATAL_ERROR "pkg-config not found")
endif()

pkg_check_modules(GTK3 REQUIRED gtk+-3.0>=3.22)
pkg_check_modules(GMODULE_EXPORT REQUIRED gmodule-export-2.0>=2.56)

# C++ Standard
if (NOT MSVC)
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

add_subdirectory(externals)
add_subdirectory(src)
