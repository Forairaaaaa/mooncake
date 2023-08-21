/**
 * @file mooncake_framework_test.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <mooncake.h>


using namespace MOONCAKE;



/* ---------------------- App_1111 ---------------------- */
/* Create a new app with new lifecycle methods */
class App_1111 : public APP_BASE
{
    public: App_1111() { std::cout << "App-1111 constructor\n"; }
    public: ~App_1111() { std::cout << "App-1111 destructor\n"; }
};
/* Create a new app packer with new resource and memory manager */
class App_1111_packer : public APP_PACKER_BASE
{
    public:
    std::string getAppName() override { return "App-1111"; }
    void * newApp() override { return new App_1111; }
    void deleteApp(void *app) override { delete (App_1111*)app; }
    public: App_1111_packer() { std::cout << "App-1111 packer constructor\n"; }
    public: ~App_1111_packer() { std::cout << "App-1111 packer destructor\n"; }
};
/* --------------------------------------------------- */




int main()
{
    /* Create mooncake */
    Mooncake mooncake;

    /* Init framework */
    mooncake.init();
    std::cout << "\n";
    
    /* Install an app */
    App_1111_packer* app_1111_packer = new App_1111_packer;
    mooncake.install(app_1111_packer);
    std::cout << "\n";
    /*
        App-1111 packer constructor
    */

    
    /* Create an App-1111 */
    mooncake.getAppManager()->createApp(app_1111_packer);
    std::cout << "\n";
    /*
        App-1111 constructor
    */



    // /* App should aways created in heap */
    // /* Because framework will try to free them during the destruction */
    // /* Create in stack like this will cause error when mooncake reach the end of it's lifetime */
    // App_1111_packer app_1111_packer;
    // mooncake.install(&app_1111_packer);
    
    // /* Create an App-1111 */
    // mooncake.getAppManager()->createApp(&app_1111_packer);
    
    /* Mooncake's destruction will help you to free all the apps and app packers */
    return 0;
    /*
        App-1111 destructor
        App-1111 packer destructor
    */
}
