# Framework examples

# App manager basic
add_executable(app_manager_basic ./app_manager_basic.cpp)
target_link_libraries(app_manager_basic ${PROJECT_NAME})

# App register test
add_executable(app_register_test ./app_register_test.cpp)
target_link_libraries(app_register_test ${PROJECT_NAME})

# Mooncake test
add_executable(mooncake_framework_test ./mooncake_framework_test.cpp)
target_link_libraries(mooncake_framework_test ${PROJECT_NAME})

# App user data test
add_executable(app_internal_api_test ./app_internal_api_test.cpp)
target_link_libraries(app_internal_api_test ${PROJECT_NAME})

