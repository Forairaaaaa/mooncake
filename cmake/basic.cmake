# Basic CMakeLists.txt

project(mooncake)

# Src files
file(GLOB_RECURSE MOONCAKE_SRCS
    ${MOONCAKE_ROOT_DIR}/src/*.c
    ${MOONCAKE_ROOT_DIR}/src/*.cpp
)
# Include
set(MOONCAKE_INCS
    ${MOONCAKE_ROOT_DIR}/src/
    ${MOONCAKE_ROOT_DIR}/src/spdlog/include/
)


# Builtin apps
option(MOONCAKE_BUILD_BUILTIN_APPS "Build builtin apps" ON)
if(MOONCAKE_BUILD_BUILTIN_APPS)
    file(GLOB_RECURSE MOONCAKE_BUILTIN_APPS_SRCS
        ${MOONCAKE_ROOT_DIR}/apps/*.c
        ${MOONCAKE_ROOT_DIR}/apps/*.cpp
    )
    set(MOONCAKE_BUILTIN_APPS_INCS
        ${MOONCAKE_ROOT_DIR}/apps/
    )
endif()



add_library(${PROJECT_NAME} ${MOONCAKE_SRCS} ${MOONCAKE_BUILTIN_APPS_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${MOONCAKE_INCS} ${MOONCAKE_BUILTIN_APPS_INCS})


option(MOONCAKE_BUILD_EXAMPLE "Build example" ON)


# Example
if(MOONCAKE_BUILD_EXAMPLE)
    add_subdirectory(./example/)
endif()
