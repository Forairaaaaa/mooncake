/**
 * @file wf_user_custom.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "wf_user_custom.h"
#include "../assets/assets.h"




namespace MOONCAKE {
    namespace BUILTIN_APP {


        void WF_User_Custom::_lvgl_event_cb(lv_event_t* e)
        {
            /* Get event code */
            lv_event_code_t code = lv_event_get_code(e);

            /* Play anim */
            if (code == LV_EVENT_CLICKED) {
                // printf("clicked\n");

            }

            /* Quit */
            else if (code == LV_EVENT_GESTURE) {
                // printf("gesture\n");

                WF_User_Custom* app = (WF_User_Custom*)lv_event_get_user_data(e);

                if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
                    app->destroyApp();
                }
            }
        }


        void WF_User_Custom::_update_data()
        {


            printf("666\n");
        }


        void WF_User_Custom::onSetup()
        {
            setAppName("Spring Wreath");
            setAllowBgRunning(false);
            setAppIcon(nullptr);
        }


        /* Life cycle */
        void WF_User_Custom::onCreate()
        {
            printf("[%s] onCreate\n", getAppName().c_str());


            /* Get data's pointer from database */
            _data.time_ptr = (DataTime_t*)getDatabase()->Get(MC_TIME)->addr;
            _data.just_wake_up_ptr = (bool*)getDatabase()->Get(MC_JUST_WAKEUP)->addr;
            _data.key_pwr_home_ptr = (bool*)getDatabase()->Get(MC_KEY_HOME)->addr;


            /* Create screen */
            _data.screen = lv_obj_create(NULL);
            lv_scr_load_anim(_data.screen, LV_SCR_LOAD_ANIM_FADE_IN, 50, 0, false);
            /* Set background color */
            lv_obj_set_style_bg_color(_data.screen, lv_color_hex(0x000000), LV_STATE_DEFAULT);
            /* Add event callback */
            lv_obj_add_event_cb(_data.screen, _lvgl_event_cb, LV_EVENT_ALL, (void*)this);



        }


        void WF_User_Custom::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());

        }


        void WF_User_Custom::onRunning()
        {
            /* Update data */
            if ((lv_tick_get() - _data.update_count) > _data.update_interval) {
                _update_data();
                _data.update_count = lv_tick_get();
            }

            /* If just wake up */
            if (*_data.just_wake_up_ptr) {
                /* Reset */
                *_data.just_wake_up_ptr = false;

                /* Update data at once */
                _update_data();
            }

            /* If pressed key Home */
            if (*_data.key_pwr_home_ptr) {
                /* Reset */
                *_data.key_pwr_home_ptr = false;

                /* Quit */
                destroyApp();
            }
        }


        void WF_User_Custom::onRunningBG()
        {

        }


        void WF_User_Custom::onPause()
        {
            printf("[%s] onPause\n", getAppName().c_str());
        }


        void WF_User_Custom::onDestroy()
        {
            printf("[%s] onDestroy\n", getAppName().c_str());
        }



    }
}

