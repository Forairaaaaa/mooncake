/**
 * @file launcher.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "launcher.h"
#include "../../system_data_def.h"


namespace MOONCAKE {
    namespace BUILTIN_APP {


        void Launcher::onSetup()
        {
            setAppName("Launcher");
            setAllowBgRunning(true);
            _framework = (Framework*)getUserData();

        }


        /* Life cycle */
        void Launcher::onCreate()
        {
            printf("[%s] onCreate\n", getAppName().c_str());



            _launcher_screen = lv_obj_create(NULL);
            




        }


        void Launcher::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());


            lv_scr_load_anim(_launcher_screen, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, true);
        }


        void Launcher::onRunning()
        {
            // printf("[%s] onRunning\n", getAppName().c_str());

            

            
        }


        void Launcher::onRunningBG()
        {
            printf("[%s] onRunningBG\n", getAppName().c_str());



        }


        void Launcher::onPause()
        {
            printf("[%s] onPause\n", getAppName().c_str());
        }


        void Launcher::onDestroy()
        {
            printf("[%s] onDestroy\n", getAppName().c_str());
        }


    }
}
