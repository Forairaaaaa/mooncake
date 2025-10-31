/**
 * @file launcher.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2025-10-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <mooncake.h>
#include <algorithm>

namespace mooncake {
namespace templates {

/**
 * @brief 启动器模板基类
 * 实现一个单 App 的启动器：当打开一个 App 后, 启动器被关闭, 进入睡眠态
 * 当被打开的 App 结束, 进入睡眠态后, 启动器重新打开, 进入运行态
 *
 */
class AppLauncherBase : public AppAbility {
public:
    /**
     * @brief 尝试打开 App
     *
     * @param appID
     * @return true
     * @return false
     */
    bool openApp(int appID)
    {
        // Check if it's itself
        if (appID == getID()) {
            return false;
        }

        // Check if app exist
        if (GetMooncake().isAppExist(appID)) {
            _going_to_open_app_id = appID;
            return true;
        }

        return false;
    }

    /**
     * @brief 获取所有已安装的 App 属性, 不包含启动器
     *
     * @return std::vector<AppProps_t>
     */
    std::vector<AppProps_t> getAppProps()
    {
        auto app_props = GetMooncake().getAllAppProps();

        // Remove launcher from list
        auto it = std::find_if(app_props.begin(), app_props.end(),
                               [this](const auto& item) { return item.appID == getID(); });
        if (it != app_props.end()) {
            app_props.erase(it);
        }

        return app_props;
    }

    inline bool isAppRunning()
    {
        return _running_app_id >= 0;
    }

    inline int getRunningAppId()
    {
        return _running_app_id;
    }

    // 生命周期回调
    virtual void onLauncherCreate() {}
    virtual void onLauncherOpen()
    {
        // 使用 getAppProps() 获取已安装的 App 属性
        // 创建或显示启动器 UI
    }
    virtual void onLauncherRunning()
    {
        // 更新 UI, 检测事件等
        // 如果选中, 使用 openApp 打开 App
    }
    virtual void onLauncherSleeping()
    {
        // 销毁或隐藏启动器 UI
    }
    virtual void onLauncherClose() {}
    virtual void onLauncherDestroy() {}

    void onCreate() override
    {
        setAppInfo().name = "Launcher";
        onLauncherCreate();
    }

    void onOpen() override
    {
        onLauncherOpen();
    }

    void onRunning() override
    {
        // If there is an app to open
        if (_going_to_open_app_id >= 0) {
            // Open new app
            if (GetMooncake().openApp(_going_to_open_app_id)) {
                _running_app_id = _going_to_open_app_id;
                _going_to_open_app_id = -1;

                // Close laucnher
                close();
                return;
            }
            _going_to_open_app_id = -1;
        }

        onLauncherRunning();
    }

    void onSleeping() override
    {
        // If an app is opened and running
        if (isAppRunning()) {
            // If running app is closed
            if (GetMooncake().getAppCurrentState(getRunningAppId()) == AppAbility::StateSleeping) {
                _running_app_id = -1;

                // Open launcher
                open();
                return;
            }
        }

        onLauncherSleeping();
    }

    void onClose() override
    {
        onLauncherClose();
    }

    void onDestroy() override
    {
        onLauncherDestroy();
    }

protected:
    int _running_app_id = -1;
    int _going_to_open_app_id = -1;
};

} // namespace templates
} // namespace mooncake
