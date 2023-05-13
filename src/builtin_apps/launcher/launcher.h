/**
 * @file launcher.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../app/app.h"
#include "../../framework/framework.h"

#include <lvgl.h>


namespace MOONCAKE {
    namespace BUILTIN_APP {


        struct LauncherData_t {
            int16_t* dispHor = nullptr;
            int16_t* dispVer = nullptr;
            bool dispModePortrait = false;
            lv_obj_t* screenMain = nullptr;
            lv_obj_t* appFlexCntr = nullptr;
        };

    
        class Launcher : public APP_BASE {
            private:
                Framework* _framework;
                APP_BASE* _launch_app;

                /* Lvgl */
                LauncherData_t _data;
                static void _lvgl_event_cb(lv_event_t* e);
                void _update_app_list();


            public:
                Launcher() : _framework(nullptr), _launch_app(nullptr) {}
                ~Launcher() = default;

                void updateAppIconZoom();
                inline void setLaunchApp(APP_BASE* app) { _launch_app = app; }


                /**
                 * @brief Lifecycle callbacks for derived to override
                 * 
                 */
                /* Setup App configs, called when App "install()" */
                void onSetup();

                /* Life cycle */
                void onCreate();
                void onResume();
                void onRunning();
                void onRunningBG();
                void onPause();
                void onDestroy();
            
        };


        class Launcher_BubbleCloud : public APP_BASE {
            private:
                Framework* _framework;
                APP_BASE* _launch_app;

                /* Lvgl */
                LauncherData_t _data;


            public:
                Launcher_BubbleCloud() : _framework(nullptr), _launch_app(nullptr) {}
                ~Launcher_BubbleCloud() = default;

                void updateAppIconZoom();
                inline void setLaunchApp(APP_BASE* app) { _launch_app = app; }


                /**
                 * @brief Lifecycle callbacks for derived to override
                 * 
                 */
                /* Setup App configs, called when App "install()" */
                void onSetup();

                /* Life cycle */
                void onCreate();
                void onResume();
                void onRunning();
                void onRunningBG();
                void onPause();
                void onDestroy();
            
        };


    }
}
