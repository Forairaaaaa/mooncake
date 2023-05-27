/**
 * @file wf_spring_wreath.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "wf_spring_wreath.h"
#include "../assets/assets.h"


namespace MOONCAKE {
    namespace BUILTIN_APP {


        void WF_Spring_Wreath::onSetup()
        {
            setAppName("Spring Wreath");
            setAllowBgRunning(false);
            setAppIcon((void*)&ui_img_app_icon_hdpi_wf_spring_wreath_png);
        }


        /* Life cycle */
        void WF_Spring_Wreath::onCreate()
        {
            printf("[%s] onCreate\n", getAppName().c_str());


            destroyApp();
        }


        void WF_Spring_Wreath::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());

        }


        void WF_Spring_Wreath::onRunning()
        {

        }


        void WF_Spring_Wreath::onRunningBG()
        {

        }


        void WF_Spring_Wreath::onPause()
        {
            printf("[%s] onPause\n", getAppName().c_str());
        }


        void WF_Spring_Wreath::onDestroy()
        {
            printf("[%s] onDestroy\n", getAppName().c_str());
        }



    }
}
