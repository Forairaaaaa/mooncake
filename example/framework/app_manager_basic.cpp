/**
 * @file app_manager_basic.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <app/app_manager.h>


using namespace MOONCAKE;



/* ---------------------- App_1111 ---------------------- */
/* Create a new app with new lifecycle methods */
class App_1111 : public APP_BASE
{
    void onCreate() override
    {
        std::cout << getAppName() << " > onCreate\n";
        // startApp();
    }
    void onResume() override
    {
        std::cout << getAppName() << " > onResume\n";
    }
    void onRunning() override
    {
        std::cout << getAppName() << " > onRunning\n";
    }
    void onPause() override
    {
        std::cout << getAppName() << " > onPause\n";
    }
    void onDestroy() override
    {
        std::cout << getAppName() << " > onDestroy\n";
    }
    public: ~App_1111()
    {
        std::cout << getAppName() << " > I'm deleted :(\n";
    }
};
/* Create a new app packer with new resource and memory manager */
class App_1111_packer : public APP_PACKER_BASE
{
    std::string getAppName() override { return "App-1111"; }
    void * newApp() override { return new App_1111; }
    void deleteApp(void *app) override { delete (App_1111*)app; }
};
/* --------------------------------------------------- */


/* ---------------------- App_2222 ---------------------- */
/* Create a new app with new lifecycle methods */
class App_2222 : public APP_BASE
{
    void onCreate() override
    {
        std::cout << getAppName() << " > onCreate, hi!\n";
    }
    void onResume() override
    {
        std::cout << getAppName() << " > onResume\n";
    }
    void onRunning() override
    {
        std::cout << getAppName() << " > onRunning, I want to be destroyed!\n";
        destroyApp();
    }
    void onPause() override
    {
        std::cout << getAppName() << " > onPause\n";
    }
    void onDestroy() override
    {
        std::cout << getAppName() << " > onDestroy, bye!\n";
    }
    public: ~App_2222()
    {
        std::cout << getAppName() << " > I'm deleted :(\n";
    }
};
/* Create a new app packer with new resource and memory manager */
class App_2222_packer : public APP_PACKER_BASE
{
    std::string getAppName() override { return "App-2222"; }
    void * newApp() override { return new App_2222; }
    void deleteApp(void *app) override { delete (App_2222*)app; }
};
/* --------------------------------------------------- */




int main()
{
    std::cout << "[App manager basic example]\n\n";


    /* Create a app manager */
    APP_Manager app_manager;


    /* "App_1111_packer" contains "App_1111"'s basic resouces, and methods to actually create and delete an "App_1111" */
    App_1111_packer app_1111_packer;
    /* So do "App_2222_packer" to the "App_2222" */
    App_2222_packer app_2222_packer;
    

    /* Use createApp() to instantiate an app */
    /* Manager will instantiate an app by the app packer we pass */
    /* And store them inside, return a pointer for you to controll the app's lifecycle */
    APP_BASE* app_1111_ptr = app_manager.createApp(app_1111_packer.getAddr());
    APP_BASE* app_2222_ptr = app_manager.createApp(app_2222_packer.getAddr());
    /* Two apps' onCreate() should be called already, and you can see the output on console: */
    /*
        App-1111 > onCreate
        App-2222 > onCreate, hi!
    */


    /* Now we can call update() to keep our apps running */
    for (int i = 0; i < 66; i++)
        app_manager.update();
    /* But nothing happened, because they're not "start" yet */
    /* We can start them manually, with the pointers we're just got */
    /* Or we can call "startApp()" inside the app like line-26 */
    /* So the app will start automatically after it's creation */


    /* Let's start them manually and try again */
    std::cout << "\n";
    app_manager.startApp(app_1111_ptr);
    app_manager.startApp(app_2222_ptr);
    for (int i = 0; i < 6; i++)
        app_manager.update();
    /* Now we have some output: */
    /*
        App-1111 > onResume
        App-2222 > onResume
        App-1111 > onRunning
        App-2222 > onRunning, I want to be destroyed!
        App-1111 > onRunning
        App-2222 > onPause
        App-2222 > onDestroy, bye!
        App-2222 > I'm deleted :(
        App-1111 > onRunning
        App-1111 > onRunning
        App-1111 > onRunning
    */
    /* We can see that App-1111 was kept running (logging) */
    /* But App-2222 was destroyed, because "destroyApp()" was called inside the app at line-74 */
    /* which tells the manager to destroy it in next update() */

    /* Since we called "update()" 6 times */
    /* We can slice the above output like this: */
    /*
        1)  App-1111 > onResume
            App-2222 > onResume
        2)  App-1111 > onRunning
            App-2222 > onRunning, I want to be destroyed!
        3)  App-1111 > onRunning
            App-2222 > onPause
            App-2222 > onDestroy, bye!
            App-2222 > I'm deleted :(
        4)  App-1111 > onRunning
        5)  App-1111 > onRunning
        6)  App-1111 > onRunning
    */

    
    /* Now we can try to destroy App-1111 manually */
    std::cout << "\n";
    app_manager.destroyApp(app_1111_ptr);
    /* We can see that App-1111 is now destroyed */
    /*
        App-1111 > onPause
        App-1111 > onDestroy
        App-1111 > I'm deleted :(
    */


    /* Try calling update again */
    for (int i = 0; i < 66; i++)
        app_manager.update();
    /* There's no more output, because: */
    std::cout << "\napp manager now have " << app_manager.getTotalAppNum() << " apps\n";
    /*
        app manager now have 0 apps
    */


    return 0;
}
