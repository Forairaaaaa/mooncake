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
    /**
     * @brief 打印关于信息
     *
     */
    void logAboutMsg();

    /**
     * @brief 更新 Mooncake，刷新 App 及 Extension 状态，触发生命周期回调
     *
     */
    void update();

    /* -------------------------------------------------------------------------- */
    /*                             App Ability Manager                            */
    /* -------------------------------------------------------------------------- */
    // App Ability 管理器 API 封装

    /**
     * @brief 安装 App，返回 App ID
     *
     * @param appAbility
     * @return int
     */
    int installApp(std::unique_ptr<AppAbility> appAbility);

    /**
     * @brief 卸载指定 ID 的 App
     *
     * @param appID
     * @return true
     * @return false
     */
    bool uninstallApp(int appID);

    /**
     * @brief 卸载所有 App
     *
     */
    void uninstallAllApps();

    /**
     * @brief 打开指定 ID 的 App
     *
     * @param appID
     * @return true
     * @return false
     */
    bool openApp(int appID);

    /**
     * @brief 关闭指定 ID 的 App
     *
     * @param appID
     * @return true
     * @return false
     */
    bool closeApp(int appID);

    /**
     * @brief 检查 App 是否存在
     *
     * @param appID
     * @return true
     * @return false
     */
    bool isAppExist(int appID);

    /**
     * @brief 获取当前 App 数量
     *
     * @return std::size_t
     */
    std::size_t getAppNum();

    /**
     * @brief 获取指定 ID 的 App 信息
     *
     * @param appID
     * @return AppAbility::AppInfo_t
     */
    AppAbility::AppInfo_t getAppInfo(int appID);

    /**
     * @brief 获取所有 App 的 App 信息
     *
     * @return std::vector<AppAbility::AppInfo_t>
     */
    std::vector<AppAbility::AppInfo_t> getAllAppInfo();

    /**
     * @brief 获取指定 ID 的 App 当前生命周期状态
     *
     * @param appID
     * @return AppAbility::State_t
     */
    AppAbility::State_t getAppCurrentState(int appID);

    /* -------------------------------------------------------------------------- */
    /*                          Extension Ability Manager                         */
    /* -------------------------------------------------------------------------- */
    // Extension Ability 管理器 API 封装。
    // 因为 Extension 可以是任意 Ability 类型，所以直接懒加载，暴露管理器实例就算 9 数了

    /**
     * @brief 获取 Extension Ability 管理器实例
     *
     * @return AbilityManager*
     */
    AbilityManager* ExtensionManager();

    /**
     * @brief 重置 Extension Ability 管理器，销毁其中所有 Ability
     *
     */
    void resetExtensionManager();

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
