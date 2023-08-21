# Framework examples

# Simplekv test
add_executable(simplekv_test ./simplekv_test.cpp)
target_link_libraries(simplekv_test ${PROJECT_NAME})

# App manager basic
add_executable(app_manager_basic ./app_manager_basic.cpp)
target_link_libraries(app_manager_basic ${PROJECT_NAME})

# Mooncake basic
add_executable(mooncake_basic ./mooncake_basic.cpp)
target_link_libraries(mooncake_basic ${PROJECT_NAME})

# Input device register basic
add_executable(input_device_register_test ./input_device_register_test.cpp)
target_link_libraries(input_device_register_test ${PROJECT_NAME})

