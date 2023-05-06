# Basic CMakeLists.txt

# Source files 
file(GLOB_RECURSE MOONCAKE_SRCS
    ${MOONCAKE_ROOT_DIR}/src/hal/*.cpp
    ${MOONCAKE_ROOT_DIR}/src/hal/platform/linux_sdl/*.cpp
)

#  Build library
add_library(mooncake ${MOONCAKE_SRCS})

# Include
target_include_directories(mooncake PUBLIC
    ${MOONCAKE_ROOT_DIR}/src/
    ${MOONCAKE_ROOT_DIR}/src/hal/
    ${MOONCAKE_ROOT_DIR}/src/hal/platform/linux_sdl/
)