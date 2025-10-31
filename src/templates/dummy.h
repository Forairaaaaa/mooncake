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
#include <cstdio>

namespace mooncake {
namespace templates {

class AppDummy : public AppAbility {
public:
    void onCreate() override
    {
        static int dummy_id = 0;
        dummy_id++;
        setAppInfo().name = "Dummy" + std::to_string(dummy_id);

        std::printf("%s onCreate\n", getAppInfo().name.c_str());
    }

    void onOpen() override
    {
        std::printf("%s onOpen\n", getAppInfo().name.c_str());
    }

    void onRunning() override
    {
        std::printf("%s onRunning\n", getAppInfo().name.c_str());
    }

    void onSleeping() override
    {
        std::printf("%s onSleeping\n", getAppInfo().name.c_str());
    }

    void onClose() override
    {
        std::printf("%s onClose\n", getAppInfo().name.c_str());
    }

    void onDestroy() override
    {
        std::printf("%s onDestroy\n", getAppInfo().name.c_str());
    }
};

} // namespace templates
} // namespace mooncake
