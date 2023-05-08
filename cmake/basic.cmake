# Basic CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)#C11
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Mooncake
file(GLOB_RECURSE MOONCAKE_SRCS
    ${MOONCAKE_ROOT_DIR}/src/app/*.cpp
    ${MOONCAKE_ROOT_DIR}/src/framework/*.cpp
)
set(MOONCAKE_INCS
    ${MOONCAKE_ROOT_DIR}/src/
    ${MOONCAKE_ROOT_DIR}/app/
    ${MOONCAKE_ROOT_DIR}/framework/
)


# SimpleKV
set(SIMPLEKV_SRCS
    ${MOONCAKE_ROOT_DIR}/src/simplekv/simplekv.cpp
)
set(SIMPLEKV_INCS
    ${MOONCAKE_ROOT_DIR}/src/simplekv/
)


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
target_link_libraries(mooncake PUBLIC lvgl lvgl::examples lvgl::demos)
