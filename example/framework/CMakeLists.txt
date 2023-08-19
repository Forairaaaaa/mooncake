# Framework examples

# simplekv test
add_executable(simplekv_test ./simplekv_test.cpp)
target_link_libraries(simplekv_test ${PROJECT_NAME})

# app manager test
add_executable(app_manager_basic ./app_manager_basic.cpp)
target_link_libraries(app_manager_basic ${PROJECT_NAME})
