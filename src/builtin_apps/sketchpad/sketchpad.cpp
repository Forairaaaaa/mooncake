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

            /* Drawing */
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


            /* Create canvas buffer */
            // static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];
            _data.canvas_buffer = new lv_color_t[LV_CANVAS_BUF_SIZE_TRUE_COLOR(lv_obj_get_width(_data.screen), lv_obj_get_height(_data.screen))];
            printf("[%s] alloc buffer %d x %d\n", getAppName().c_str(), lv_obj_get_width(_data.screen), lv_obj_get_height(_data.screen));

            /*Create a canvas and initialize its palette*/
            _data.canvas = lv_canvas_create(_data.screen);
            lv_canvas_set_buffer(_data.canvas, _data.canvas_buffer, lv_obj_get_width(_data.screen), lv_obj_get_height(_data.screen), LV_IMG_CF_TRUE_COLOR);
            lv_obj_center(_data.canvas);
            lv_canvas_fill_bg(_data.canvas, lv_color_hex(0x000000), LV_OPA_COVER);

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
            
            /* Free buffer */
            /* Stop lvgl use that buffer before freeing */
            lv_canvas_set_buffer(_data.canvas, _data.canvas_buffer, 0, 0, LV_IMG_CF_TRUE_COLOR);
            delete [] _data.canvas_buffer;
        }



    }
}
