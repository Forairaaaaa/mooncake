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
#include <lvgl.h>


namespace MOONCAKE {
    namespace BUILTIN_APP {


        void Launcher::onSetup()
        {
            setAppName("Launcher");
            setAllowBgRunning(true);

            _framework = (Framework*)getUserData();

            printf("app num :::: %d\n", _framework->getAppNum());
        }


        /* Life cycle */
        void Launcher::onCreate()
        {
            printf("%s > onCreate\n", getAppName().c_str());

            
        }


        void Launcher::onResume()
        {
            printf("%s > onResume\n", getAppName().c_str());


        }


        void Launcher::onRunning()
        {
            printf("%s > onRunning\n", getAppName().c_str());

            
            _framework->closeApp(getAppName().c_str());
            
        }


        void Launcher::onRunningBG()
        {
            printf("%s > onRunningBG\n", getAppName().c_str());


            // _framework->destroyApp(getAppName().c_str());
            // _framework->startApp(getAppName().c_str());


        }


        void Launcher::onPause()
        {
            printf("%s > onPause\n", getAppName().c_str());
        }


        void Launcher::onDestroy()
        {
            printf("%s > onDestroy\n", getAppName().c_str());
        }


    }
}
