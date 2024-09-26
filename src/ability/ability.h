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

namespace Mooncake {

namespace AbilityType {
enum Type_t {
    None = 0,
    Basic,
    UI,
    Worker,
    Custom,
};
}

/**
 * @brief Ability 基类，提供原始生命周期回调，以便管理器统一调用
 *
 */
class AbilityBase {
public:
    virtual ~AbilityBase() = default;

public:
    virtual AbilityType::Type_t getAbilityType()
    {
        return AbilityType::None;
    }

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

    AbilityType::Type_t getAbilityType() override
    {
        return AbilityType::Basic;
    }

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

    AbilityType::Type_t getAbilityType() override
    {
        return AbilityType::UI;
    }

    /**
     * @brief Show ability from background to foreground
     *
     */
    void show();

    /**
     * @brief Hide ability from foreground to background
     *
     */
    void hide();

    /* -------------------------------------------------------------------------- */
    /*                             Lifecycle callbacks                            */
    /* -------------------------------------------------------------------------- */
    virtual void onCreate() {}
    virtual void onShow() {}
    virtual void onForeground() {}
    virtual void onBackground() {}
    virtual void onHide() {}
    virtual void onDestroy() {}

private:
    enum AbilityState_t {
        StateOnShow = 0,
        StateOnForeground,
        StateOnHide,
        StateOnBackground,
    };
    AbilityState_t current_state = StateOnForeground;

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

    AbilityType::Type_t getAbilityType() override
    {
        return AbilityType::Worker;
    }

    /* -------------------------------------------------------------------------- */
    /*                             Lifecycle callbacks                            */
    /* -------------------------------------------------------------------------- */
    virtual void onCreate() {}
    virtual void onResume() {}
    virtual void onRunning() {}
    virtual void onPause() {}
    virtual void onDestroy() {}

private:
    void baseCreate() override;
    void baseUpdate() override;
    void baseDestroy() override;
};

} // namespace Mooncake