/**
 * @file launcher_bubble_cloud.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "launcher.h"
#include "../../system_data_def.h"


LV_IMG_DECLARE(ui_img_icon_hdpi_default_png);


namespace MOONCAKE {
    namespace BUILTIN_APP {



        void Launcher_BubbleCloud::onSetup()
        {
            setAppName("Launcher");
            setAllowBgRunning(true);

            /* Get framework control */
            _framework = (Framework*)getUserData();
        }


        /* Life cycle */
        void Launcher_BubbleCloud::onCreate()
        {
            printf("[%s] onCreate\n", getAppName().c_str());

            /* Get hardware infos from database */
            _data.dispHor = (int16_t*)getDatabase()->Get(MC_DISP_HOR)->addr;
            _data.dispVer = (int16_t*)getDatabase()->Get(MC_DISP_VER)->addr;

            /* Get display mode */
            if (*_data.dispHor < *_data.dispVer) {
                _data.dispModePortrait = true;
            }

            /* Crete main screen */
            _data.screenMain = lv_obj_create(NULL);
            // lv_obj_set_style_bg_color(_data.screenMain, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);

            
        }


        void Launcher_BubbleCloud::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());


            
            /* Load main screen and delete last one */
            if (lv_scr_act() != _data.screenMain) {
                lv_scr_load_anim(_data.screenMain, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, true);
            }

        }


        void Launcher_BubbleCloud::onRunning()
        {
            // printf("[%s] onRunning\n", getAppName().c_str());

            

            // _framework->closeApp(this);



  

            
        }


        void Launcher_BubbleCloud::onRunningBG()
        {
            // printf("[%s] onRunningBG\n", getAppName().c_str());

            // printf("%d\n", _framework->isAnyAppRunningFG());

            /* If no App is running on foreground */
            if (!_framework->isAnyAppRunningFG()) {
                _framework->startApp(this);
            }



        }


        void Launcher_BubbleCloud::onPause()
        {
            printf("[%s] onPause\n", getAppName().c_str());
        }


        void Launcher_BubbleCloud::onDestroy()
        {
            printf("[%s] onDestroy\n", getAppName().c_str());
        }


    }
}
