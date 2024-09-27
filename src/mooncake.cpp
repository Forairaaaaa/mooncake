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

using namespace mooncake;

void Mooncake::init() {}

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
