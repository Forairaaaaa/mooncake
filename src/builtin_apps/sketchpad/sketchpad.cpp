/**
 * @file sketchpad.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "sketchpad.h"
#include "../assets/assets.h"


namespace MOONCAKE {
    namespace BUILTIN_APP {


        void Sketchpad::_lvgl_event_cb(lv_event_t* e)
        {
            /* Get event code */
            lv_event_code_t code = lv_event_get_code(e);

            /* Quit */
            if (code == LV_EVENT_GESTURE) {
                // printf("gesture\n");

                Sketchpad* app = (Sketchpad*)lv_event_get_user_data(e);

                if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
                    app->destroyApp();
                }
            }

            if (code == LV_EVENT_PRESSING) {
                lv_point_t tp;
                lv_indev_get_point(lv_indev_get_act(), &tp);

                printf("%d %d\n", tp.x, tp.y);
            }
            
        }


        void Sketchpad::onSetup()
        {
            setAppName("Sketchpad");
            setAllowBgRunning(false);
            setAppIcon((void*)&ui_img_app_icon_hdpi_sketchpad_png);
        }


        /* Life cycle */
        void Sketchpad::onCreate()
        {
            printf("[%s] onCreate\n", getAppName().c_str());


            /* Get data's pointer from database */
            _data.key_pwr_home_ptr = (bool*)getDatabase()->Get(MC_KEY_HOME)->addr;


            /* Create screen */
            _data.screen = lv_obj_create(NULL);
            lv_scr_load_anim(_data.screen, LV_SCR_LOAD_ANIM_FADE_IN, 50, 0, false);
            /* Set background color */
            lv_obj_set_style_bg_color(_data.screen, lv_color_hex(0x000000), LV_STATE_DEFAULT);
            /* Add event callback */
            lv_obj_add_event_cb(_data.screen, _lvgl_event_cb, LV_EVENT_ALL, (void*)this);



        }


        void Sketchpad::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());

        }


        void Sketchpad::onRunning()
        {
            




        }


        void Sketchpad::onRunningBG()
        {

        }


        void Sketchpad::onPause()
        {
            printf("[%s] onPause\n", getAppName().c_str());
        }


        void Sketchpad::onDestroy()
        {
            printf("[%s] onDestroy\n", getAppName().c_str());
        }



    }
}
