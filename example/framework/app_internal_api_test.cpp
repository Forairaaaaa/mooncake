/**
 * @file app_internal_api_test.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-04-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <mooncake.h>

using namespace MOONCAKE;

/* ---------------------- App_1111 ---------------------- */
/* Create a new app with new lifecycle methods */
class App_1111 : public APP_BASE
{
    void onCreate() override { startApp(); }
    void onRunning() override
    {
        /* Frame work define wrap */
        std::cout << mcAppGetFramework()->getInstalledAppList()[0]->getAppName() << "\n";
    }
};
/* Create a new app packer with new resource and memory manager */
class App_1111_packer : public APP_PACKER_BASE
{
public:
    const char* getAppName() override { return "App-1111"; }
    void* newApp() override { return new App_1111; }
    void deleteApp(void* app) override { delete (App_1111*)app; }
};
/* ------------------------------------------------------- */

int main()
{
    std::cout << "[App internal api test]\n";

    Mooncake mooncake;
    mooncake.init();

    mooncake.installApp(new App_1111_packer);
    mooncake.createApp(mooncake.getInstalledAppList()[0]);

    for (int i = 0; i < 6; i++)
        mooncake.update();

    std::cout << "done\n";

    return 0;
}
