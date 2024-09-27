/**
 * @file mooncake.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "mooncake.h"
#include <memory>
#include <stdio.h>

using namespace mooncake;

static const char* _mooncake_ascii_logo = R"(
 _____ _____ _____ _____ _____ _____ _____ _____
|     |     |     |   | |     |  _  |  |  |   __|
| | | |  |  |  |  | | | |   --|     |    -|   __|
|_|_|_|_____|_____|_|___|_____|__|__|__|__|_____|
)";

void Mooncake::init()
{
    printf("%s\n", _mooncake_ascii_logo);
    printf("- @author Forairaaaaa\n");
    printf("- @version " MOONCAKE_VERSION "\n");
    printf("- @build at " __TIME__ " " __DATE__ "\n\n");
}

AbilityManager* Mooncake::get_app_ability_manager()
{
    if (_app_ability_manager == nullptr) {
        _app_ability_manager = std::make_unique<AbilityManager>();
    }
    return _app_ability_manager.get();
}

AbilityManager* Mooncake::get_extension_ability_manager()
{
    if (_extension_ability_manager == nullptr) {
        _extension_ability_manager = std::make_unique<AbilityManager>();
    }
    return _extension_ability_manager.get();
}
