/**
 * @file mooncake_basic.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-08-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "app/app.h"
#include "spdlog/spdlog.h"
#include <cstdint>
#include <iostream>
#include <mooncake.h>

using namespace MOONCAKE;

/* -------------------------------------------------------------------------- */
/*                          Create your app like this                         */
/* -------------------------------------------------------------------------- */
class MyApp : public APP_BASE
{
    // Like setup()
    void onResume() override { spdlog::info("hi"); }

    // Like loop()
    void onRunning() override { spdlog::info("6"); }
};

class MyAppPacker : public APP_PACKER_BASE
{
    void* newApp() override { return new MyApp; }
    void deleteApp(void* app) override { delete (MyApp*)app; }
};

int main()
{
    // Create framework and init
    Mooncake mooncake;
    mooncake.init();

    // Install your app by app packer
    // so that mooncake konws how to create and destroy your app
    mooncake.installApp(new MyAppPacker);

    // After app installed, we can get the packer pointer back from the installed list
    auto my_app_packer = mooncake.getInstalledAppList()[0];

    // Tell mooncake to create an instance of your app, and start it
    mooncake.createAndStartApp(my_app_packer);

    // Keep framework running
    for (int i = 0; i < 10; i++)
        mooncake.update();

    // Mooncake will help you destroy every app and packers' instance
    return 0;
}
