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
#include <lvgl.h>


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

            // lv_demo_benchmark(LV_DEMO_BENCHMARK_MODE_REAL);

        }


        void Boot_Anim::onResume()
        {

        }


        void Boot_Anim::onRunning()
        {
            count++;
            // printf("%d\n", count);
            if (count == 0xFF) {
                endApp();
            }

            lv_timer_handler();
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
