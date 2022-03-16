
# basicini
add_subdirectory(basicini EXCLUDE_FROM_ALL)
target_include_directories(basicini INTERFACE ./basicini/src)

# yuzu common
add_subdirectory(./yuzu/src/common EXCLUDE_FROM_ALL)
target_include_directories(common PUBLIC ./yuzu/src)

# MicroProfile -- yuzu common requirement
add_library(microprofile INTERFACE EXCLUDE_FROM_ALL)
target_include_directories(microprofile INTERFACE ./yuzu/externals/microprofile)

# xbyak -- yuzu common requirement
if (ARCHITECTURE_x86 OR ARCHITECTURE_x86_64)
    add_library(xbyak INTERFACE)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/xbyak/include)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/yuzu/externals/xbyak/xbyak DESTINATION
         ${CMAKE_CURRENT_BINARY_DIR}/yuzu/externals/xbyak/include)
    target_include_directories(xbyak SYSTEM INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/yuzu/externals/xbyak/include)
    target_compile_definitions(xbyak INTERFACE XBYAK_NO_OP_NAMES)
endif()
