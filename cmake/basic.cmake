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


add_library(${PROJECT_NAME} ${MOONCAKE_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${MOONCAKE_INCS})


option(MOONCAKE_BUILD_EXAMPLE "Build example" ON)


# Example
if(MOONCAKE_BUILD_EXAMPLE)
    add_subdirectory(./example/)
endif()



# CTest
enable_testing()

# Framework Test
# App manager basic
add_test(app_manager_basic example/framework/app_manager_basic)
# App register test
add_test(app_register_test example/framework/app_register_test)
# App internal api test
add_test(app_internal_api_test example/framework/app_internal_api_test)
# Mooncake framework test
add_test(mooncake_framework_test example/framework/mooncake_framework_test)


# Mooncake Test
# Mooncake basic
add_test(mooncake_basic example/mooncake/mooncake_basic)
