/**
 * @file ability_manager.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-26
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

class MyUIAbility : public UIAbility {
public:
    MyUIAbility()
    {
        printf("[ui] on construct\n");
    }
    ~MyUIAbility()
    {
        printf("[ui] on deconstruct\n");
    }
    void onCreate() override
    {
        printf("[ui] on create\n");
    }
    void onShow() override
    {
        printf("[ui] on show\n");
    }
    void onForeground() override
    {
        printf("[ui] on foreground\n");

        // 切到后台
        if (_enter_was_pressed) {
            _enter_was_pressed = false;
            hide();
        }
    }
    void onHide() override
    {
        printf("[ui] on hide\n");
    }
    void onBackground() override
    {
        printf("[ui] on backgournd\n");

        // 切到前台
        if (_enter_was_pressed) {
            _enter_was_pressed = false;
            show();
        }
    }
    void onDestroy() override
    {
        printf("[ui] on ondestory\n");
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
    auto ui_ability_id = am.createAbility(std::make_unique<MyUIAbility>());

    // 刷新 Ability
    while (1) {
        am.updateAbilities();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // 销毁 Ability
    printf(">> destroy ability\n");
    am.destroyAbility(ui_ability_id);
    am.updateAbilities();

    return 0;
}

// // 除了在 Ability 内部切换状态，还可以在外部切换，适合切换条件相同的多个 Ability 统一管理

//     // 获取 Ability 实例原始指针
//     auto ui_ability_instance = (UIAbility*)am.getAbilityInstance(ui_ability_id);
//     // 验空、调用方法
//     if (ui_ability_instance) {
//         ui_ability_instance->show();
//         ...
//     }
// }
