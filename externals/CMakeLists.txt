
# basicini
add_subdirectory(basicini EXCLUDE_FROM_ALL)
target_include_directories(basicini INTERFACE ./basicini/src)

# yuzu common
add_subdirectory(./yuzu/src/common EXCLUDE_FROM_ALL)
target_include_directories(common PUBLIC ./yuzu/src)
