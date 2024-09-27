/**
 * @file ability.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>

namespace Mooncake {

/**
 * @brief Ability 基类，提供原始生命周期回调，以便管理器统一调用
 *
 */
class AbilityBase {
public:
    virtual ~AbilityBase() = default;

public:
    virtual void baseCreate() {}
    virtual void baseUpdate() {}
    virtual void baseDestroy() {}
};

/**
 * @brief Basic Ability，提供最基础的三段式生命周期。可以把 onCreate() 理解成 Arduino 的 setup()，onRunning() 为 loop()
 *
 */
class BasicAbility : public AbilityBase {
public:
    virtual ~BasicAbility() = default;

    // 生命周期回调
    virtual void onCreate() {}
    virtual void onRunning() {}
    virtual void onDestroy() {}

private:
    void baseCreate() override
    {
        onCreate();
    }

    void baseUpdate() override
    {
        onRunning();
    }

    void baseDestroy() override
    {
        onDestroy();
    }
};

/**
 * @brief UI Ability，在三段式生命周期的基础上扩展出前后台切换。适合前后台具有不同行为的 UI
 * 应用，比如桌面启动器（选择一个 App 打开后，将自己藏进后台）
 *
 */
class UIAbility : public AbilityBase {
public:
    virtual ~UIAbility() = default;

    enum UIAbilityState_t {
        StateGoShow = 0,
        StateForeground,
        StateGoHide,
        StateBackground,
    };

    /**
     * @brief 将 UI 从后台切回前台
     *
     */
    void show();

    /**
     * @brief 将 UI 从前台切到后台
     *
     */
    void hide();

    /**
     * @brief 获取当前生命周期状态
     *
     * @return UIAbilityState_t
     */
    UIAbilityState_t currentState()
    {
        return _current_state;
    }

    // 生命周期回调
    virtual void onCreate() {}
    virtual void onShow() {}
    virtual void onForeground() {}
    virtual void onBackground() {}
    virtual void onHide() {}
    virtual void onDestroy() {}

private:
    UIAbilityState_t _current_state = StateForeground;

    void baseCreate() override;
    void baseUpdate() override;
    void baseDestroy() override;
};

/**
 * @brief Worker
 * Ability，在三段式基础上扩展出运行、暂停状态切换。适合后台应用，比如数据监听、事件转发。或者简单二元状态的 UI 行为
 *
 */
class WorkerAbility : public AbilityBase {
public:
    virtual ~WorkerAbility() = default;

    enum WorkerAbilityState_t {
        StateGoResume = 0,
        StateRunning,
        StateGoPause,
        StatePausing,
    };

    /**
     * @brief 暂停 Worker 运行
     *
     */
    void pause();

    /**
     * @brief 恢复 Worker 运行
     *
     */
    void resume();

    /**
     * @brief 获取当前生命周期状态
     *
     * @return UIAbilityState_t
     */
    WorkerAbilityState_t currentState()
    {
        return _current_state;
    }

    // 生命周期回调
    virtual void onCreate() {}
    virtual void onResume() {}
    virtual void onRunning() {}
    virtual void onPause() {}
    virtual void onDestroy() {}

private:
    WorkerAbilityState_t _current_state = StateRunning;

    void baseCreate() override;
    void baseUpdate() override;
    void baseDestroy() override;
};

/**
 * @brief App Ability，在三段式的基础上扩展出打开、关闭状态，还有基础 App 信息（名称、图标等），适合有 App
 * 信息需求的简单应用抽象
 *
 */
class AppAbility : public AbilityBase {
public:
    virtual ~AppAbility() = default;

    struct AppInfo_t {
        std::string name;
        void* icon = nullptr;
        void* userData = nullptr;
    };

    enum AppAbilityState_t {
        StateGoOpen = 0,
        StateRunning,
        StateGoClose,
        StateSleeping,
    };

    /**
     * @brief 打开 App，干活
     *
     */
    void open();

    /**
     * @brief 关闭 App，开摆
     *
     */
    void close();

    const AppInfo_t& getAppInfo();
    AppInfo_t& setAppInfo();

    // 生命周期回调
    virtual void onCreate() {}
    virtual void onOpen() {}
    virtual void onRunning() {}
    virtual void onClose() {}
    virtual void onDestroy() {}

private:
    AppAbilityState_t _current_state = StateSleeping;

    void baseCreate() override;
    void baseUpdate() override;
    void baseDestroy() override;
};

} // namespace Mooncake