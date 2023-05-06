# Basic CMakeLists.txt

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