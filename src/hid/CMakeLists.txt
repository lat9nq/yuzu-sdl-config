add_library(hid
    device.cpp
    device.h
    hid.cpp
    hid.h
)

target_include_directories(hid PRIVATE ${PROJECT_SOURCE_DIR}/externals/yuzu/src)
target_link_libraries(hid PRIVATE ${SDL2_LIBRARIES})
target_include_directories(hid PRIVATE ${SDL2_INCLUDE_DIRS})
