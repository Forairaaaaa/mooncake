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
            printf("[%s] onCreate\n", getAppName().c_str());



            lv_obj_t * label1 = lv_label_create(lv_scr_act());
            lv_label_set_text(label1, "Boot Anim");
            lv_obj_align(label1, LV_ALIGN_CENTER, 0, -30);
            

        }


        void Boot_Anim::onResume()
        {
            

        }


        void Boot_Anim::onRunning()
        {
            static lv_obj_t * label2 = lv_label_create(lv_scr_act());

            if (lv_tick_get() > 500) {
                destroyApp();
            }


            lv_label_set_text_fmt(label2, "%ld", lv_tick_get());
            lv_obj_align(label2, LV_ALIGN_CENTER, 0, 0);
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
            printf("[%s] onDestroy\n", getAppName().c_str());
        }


    }
}
