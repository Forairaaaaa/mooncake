/**
 * @file dummy.h
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
#include <string>
#include <stdio.h>

namespace mooncake {
namespace templates {

class AppDummy : public AppAbility {
public:
    void onCreate() override
    {
        static int dummy_id = 0;
        dummy_id++;
        setAppInfo().name = "Dummy" + std::to_string(dummy_id);

        printf("%s onCreate\n", getAppInfo().name.c_str());
    }

    void onOpen() override
    {
        printf("%s onOpen\n", getAppInfo().name.c_str());
    }

    void onRunning() override
    {
        printf("%s onRunning\n", getAppInfo().name.c_str());
    }

    void onSleeping() override
    {
        printf("%s onSleeping\n", getAppInfo().name.c_str());
    }

    void onClose() override
    {
        printf("%s onClose\n", getAppInfo().name.c_str());
    }

    void onDestroy() override
    {
        printf("%s onDestroy\n", getAppInfo().name.c_str());
    }
};

} // namespace templates
} // namespace mooncake
