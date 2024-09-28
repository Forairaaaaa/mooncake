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
#include "ability/ability.h"
#include <memory>
#include <stdio.h>
#include <utility>

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

int Mooncake::installApp(std::unique_ptr<AppAbility> appAbility)
{
    if (!appAbility) {
        return -1;
    }

    // 类型校验
    if (appAbility->abilityType() != AbilityType_UI) {
        return -1;
    }

    return get_app_ability_manager()->createAbility(std::move(appAbility));
}

bool Mooncake::unInstallApp(int appID)
{
    if (!_app_ability_manager) {
        return false;
    }
    return get_app_ability_manager()->destroyAbility(appID);
}

bool Mooncake::openApp(int appID)
{
    if (!_app_ability_manager) {
        return false;
    }
    return get_app_ability_manager()->openAppAbility(appID);
}

bool Mooncake::closeApp(int appID)
{
    if (!_app_ability_manager) {
        return false;
    }
    return get_app_ability_manager()->closeAppAbility(appID);
}

bool Mooncake::isAppExist(int appID)
{
    if (!_app_ability_manager) {
        return false;
    }
    return get_app_ability_manager()->isAbilityExist(appID);
}

AppAbility::AppInfo_t Mooncake::getAppInfo(int appID)
{
    if (!_app_ability_manager) {
        return AppAbility::AppInfo_t();
    }
    return get_app_ability_manager()->getAppAbilityAppInfo(appID);
}

std::vector<AppAbility::AppInfo_t> Mooncake::getAllAppInfo()
{
    std::vector<AppAbility::AppInfo_t> ret;

    if (!_app_ability_manager) {
        return ret;
    }

    auto ability_list = get_app_ability_manager()->getAllAbilityInstance();
    for (const auto& ability : ability_list) {
        ret.push_back(static_cast<AppAbility*>(ability)->getAppInfo());
    }

    return ret;
}

AppAbility::AppAbilityState_t Mooncake::getAppCurrentState(int appID)
{
    if (!_app_ability_manager) {
        return AppAbility::StateNull;
    }
    return get_app_ability_manager()->getAppAbilityCurrentState(appID);
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
