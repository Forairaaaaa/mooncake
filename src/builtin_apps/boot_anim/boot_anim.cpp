/**
 * @file boot_anim.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "boot_anim.h"


namespace MOONCAKE {
    namespace BUILTIN_APP {


        void Boot_Anim::onSetup()
        {
            setAppName("BootAnim");
        }

        /* Life cycle */
        void Boot_Anim::onCreate()
        {
            printf("%s > boot anim\n", getAppName().c_str());
            count = 0;
        }


        void Boot_Anim::onResume()
        {

        }


        void Boot_Anim::onRunning()
        {
            count++;
            // printf("%d\n", count);
            if (count > 100) {
                endApp();
            }
        }


        void Boot_Anim::onRunningBG()
        {

        }


        void Boot_Anim::onPause()
        {

        }


        void Boot_Anim::onDestroy()
        {
            printf("%s > boot anim done\n", getAppName().c_str());
        }


    }
}
