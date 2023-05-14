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
            lv_obj_t* appPanel = nullptr;
            lv_coord_t appPanelHor = 0;
            lv_coord_t appPanelVer = 0;
        };


        struct BubbleConfig_t {
            lv_coord_t iconColMax = 3;
            lv_coord_t iconSpaceX = 120;
            lv_coord_t iconSpaceY = 100;
            lv_coord_t iconXoffset = 0;
            lv_coord_t iconYoffset = 0;
        };

    
        class Launcher : public APP_BASE {
            private:
                Framework* _framework;
                APP_BASE* _launch_app;

                /* Lvgl */
                LauncherData_t _data;
                BubbleConfig_t _bubble_cfg;
                static void _lvgl_event_cb(lv_event_t* e);
                void _update_app_list();


            public:
                Launcher() : _framework(nullptr), _launch_app(nullptr) {}
                ~Launcher() = default;


                void updateAppIconZoom();


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


        struct LauncherBubbleData__t {
            int16_t* dispHor = nullptr;
            int16_t* dispVer = nullptr;
            bool dispModePortrait = false;

            lv_obj_t* screenMain = nullptr;
            lv_obj_t* screenCanvas = nullptr;
            lv_color_t* canvasBuffer = nullptr;
            lv_draw_img_dsc_t iconDsc;
        };

    }
}
