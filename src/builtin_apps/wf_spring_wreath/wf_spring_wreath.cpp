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


        void WF_Spring_Wreath::_anim_update()
        {
            if (_anim.isPlaying() && ((lv_tick_get() - _anim._update_count) > _anim._update_interval)) {
                
                lv_img_set_src(_anim._img, anim_spring_wreath[_anim._index]);

                _anim._index++;
                if (_anim._index > (NUM_ANIM_SPRING_WREATH - 1)) {
                    _anim._index = 0;
                    _anim.stopPlaying();
                }
                _anim._update_count = lv_tick_get();
            }
        }


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


            /* Get data's pointer from database */
            _data.time_ptr = (DataTime_t*)getDatabase()->Get(MC_TIME)->addr;
            _data.step_counter_ptr = (uint32_t*)getDatabase()->Get(MC_STEPS)->addr;
            _data.just_wake_up_ptr = (bool*)getDatabase()->Get(MC_JUST_WAKEUP)->addr;
            _data.key_pwr_home_ptr = (bool*)getDatabase()->Get(MC_KEY_HOME)->addr;


            /* Create screen */
            _data.screen = lv_obj_create(NULL);
            lv_scr_load_anim(_data.screen, LV_SCR_LOAD_ANIM_FADE_IN, 50, 0, false);
            /* Set background color */
            lv_obj_set_style_bg_color(_data.screen, lv_color_hex(0x000000), LV_STATE_DEFAULT);


            /* Init anim */
            _anim._img = lv_img_create(_data.screen);
            lv_obj_align(_anim._img, LV_ALIGN_CENTER, 0, 0);
            _anim.setInterval(37);
            _anim.startPlaying();

        }


        void WF_Spring_Wreath::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());

        }


        void WF_Spring_Wreath::onRunning()
        {
            _anim_update();
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
