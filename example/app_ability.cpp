/**
 * @file app_ability.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <ability/ability.h>
#include <ability_manager/ability_manager.h>
#include <atomic>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

using namespace Mooncake;

std::atomic<bool> _enter_was_pressed = false;

class MyAppAbility : public AppAbility {
public:
    MyAppAbility()
    {
        printf("[app] on construct\n");

        // 配置 App 信息
        setAppInfo().name = "帅的不谈";
    }
    ~MyAppAbility()
    {
        printf("[app] on deconstruct\n");
    }
    void onCreate() override
    {
        printf("[app] on create\n");
    }
    void onOpen() override
    {
        printf("[app] on open\n");
    }
    void onRunning() override
    {
        printf("[app] on running\n");

        // 关掉 App
        if (_enter_was_pressed) {
            _enter_was_pressed = false;
            close();
        }
    }
    void onSleeping() override
    {
        printf("[app] on sleeping\n");

        // 打开 App
        if (_enter_was_pressed) {
            _enter_was_pressed = false;
            open();
        }
    }
    void onClose() override
    {
        printf("[app] on close\n");
    }
    void onDestroy() override
    {
        printf("[app] on ondestory\n");
    }
};

int main()
{
    // 创建一个线程监听回车键
    std::thread enter_listener([] {
        std::string dev_null;
        while (1) {
            std::getline(std::cin, dev_null);
            _enter_was_pressed = true;
        }
    });

    AbilityManager am;

    // 创建 Ability
    printf(">> create ability\n");
    auto app_ability_id = am.createAbility(std::make_unique<MyAppAbility>());

    // 从外部获取 App 信息
    auto app_ability_instance = (AppAbility*)am.getAbilityInstance(app_ability_id);
    printf(">> app name is: %s\n", app_ability_instance->getAppInfo().name.c_str());

    // 刷新 Ability
    while (1) {
        am.updateAbilities();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // 销毁 Ability
    printf(">> destroy ability\n");
    am.destroyAbility(app_ability_id);
    am.updateAbilities();

    return 0;
}
