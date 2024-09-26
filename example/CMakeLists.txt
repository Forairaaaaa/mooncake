# Basic
add_executable(basic ./basic.cpp)
target_link_libraries(basic ${PROJECT_NAME})

# Ability manager
add_executable(ability_manager ./ability_manager.cpp)
target_link_libraries(ability_manager ${PROJECT_NAME})
