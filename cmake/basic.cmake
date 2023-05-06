# Basic CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Mooncake
file(GLOB_RECURSE MOONCAKE_SRCS
    ${MOONCAKE_ROOT_DIR}/src/hal/platform/linux_sdl/*.cpp
)
set(MOONCAKE_INCS
    ${MOONCAKE_ROOT_DIR}/src/
    ${MOONCAKE_ROOT_DIR}/src/hal/
    ${MOONCAKE_ROOT_DIR}/src/hal/platform/linux_sdl/
)


# SimpleKV
set(SIMPLEKV_SRCS
    ${MOONCAKE_ROOT_DIR}/src/simplekv/simplekv.cpp
)
set(SIMPLEKV_INCS
    ${MOONCAKE_ROOT_DIR}/src/simplekv/
)


# SDL2
find_package(SDL2 REQUIRED SDL2)
include_directories(${SDL2_INCLUDE_DIRS})


# lvgl
set(MY_LV_CONF_PATH ${MOONCAKE_ROOT_DIR}/src/hal/platform/linux_sdl/lv_conf.h)
add_definitions(-DLV_CONF_PATH=${MY_LV_CONF_PATH})
add_subdirectory(${MOONCAKE_ROOT_DIR}/src/lvgl)




#  Build library
add_library(mooncake
    ${MOONCAKE_SRCS}
    ${SIMPLEKV_SRCS}
)


# Include
target_include_directories(mooncake PUBLIC
    ${MOONCAKE_INCS}
    ${SIMPLEKV_INCS}
)


# Link
target_link_libraries(mooncake PUBLIC ${SDL2_LIBRARIES} lvgl lvgl::examples lvgl::demos)
