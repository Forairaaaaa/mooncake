/**
 * @file mooncake.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "ability/ability.h"
#include "ability_manager/ability_manager.h"
#include <cstddef>
#include <memory>
#include <vector>

#define MOONCAKE_VERSION "2.0.0"

namespace mooncake {

class Mooncake {
public:
    void init();

    void update();

    /* -------------------------------------------------------------------------- */
    /*                                  App APIs                                  */
    /* -------------------------------------------------------------------------- */

    int installApp(std::unique_ptr<AppAbility> appAbility);
    bool unInstallApp(int appID);
    bool openApp(int appID);
    bool closeApp(int appID);
    bool isAppExist(int appID);
    std::size_t getAppNum();
    AppAbility::AppInfo_t getAppInfo(int appID);
    std::vector<AppAbility::AppInfo_t> getAllAppInfo();
    AppAbility::AppAbilityState_t getAppCurrentState(int appID);

private:
    // App Ability 管理器：提供集中的 App Ability 管理和信息获取
    std::unique_ptr<AbilityManager> _app_ability_manager;

    // Extension Ability 管理器：提供集中的杂类 Ability 管理，比如一些后台运行的 Worker，或者某些 App Ability
    // 要用到的 UI Ability、自定义 Ability 等，都可以创建在这里，由 Mooncake 集中管理
    std::unique_ptr<AbilityManager> _extension_ability_manager;

    // 懒加载
    AbilityManager* get_app_ability_manager();
    AbilityManager* get_extension_ability_manager();
};

} // namespace mooncake
