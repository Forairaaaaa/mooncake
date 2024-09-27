# Basic
add_executable(basic ./basic.cpp)
target_link_libraries(basic ${PROJECT_NAME})

# Ability manager
add_executable(ability_manager ./ability_manager.cpp)
target_link_libraries(ability_manager ${PROJECT_NAME})

# UI Ability
add_executable(ui_ability ./ui_ability.cpp)
target_link_libraries(ui_ability ${PROJECT_NAME} pthread)

# App Ability
add_executable(app_ability ./app_ability.cpp)
target_link_libraries(app_ability ${PROJECT_NAME} pthread)
