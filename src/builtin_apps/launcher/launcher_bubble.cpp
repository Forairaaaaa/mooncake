/**
 * @file launcher_bubble.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "launcher.h"
#include "../../system_data_def.h"


LV_IMG_DECLARE(ui_img_icon_hdpi_default_png);


namespace MOONCAKE {
    namespace BUILTIN_APP {



        void Launcher_Bubble::_lvgl_event_cb(lv_event_t* e)
        {
            /* Get event code */
            lv_event_code_t code = lv_event_get_code(e);




            if (code == LV_EVENT_PRESSED) {

                // printf("666\n");

                lv_point_t p;
                lv_indev_get_point(lv_indev_get_act(), &p);


                Launcher_Bubble* launcher = (Launcher_Bubble*)lv_event_get_user_data(e);
                launcher->lastTouchReset(p.x, p.y);
            }




            if (code == LV_EVENT_PRESSING) {

                lv_point_t p;
                lv_indev_get_point(lv_indev_get_act(), &p);


                Launcher_Bubble* launcher = (Launcher_Bubble*)lv_event_get_user_data(e);
                

                launcher->touchUpdate(p.x, p.y);
                launcher->bubbleUpdate();
            }




        }



        void Launcher_Bubble::lastTouchReset(lv_coord_t x, lv_coord_t y)
        {
            _bubble_status.lastTpPos.x = x;
            _bubble_status.lastTpPos.y = y;
        }



        void Launcher_Bubble::touchUpdate(lv_coord_t x, lv_coord_t y)
        {
            // printf("%d %d\n", x - _bubble_status.lastTpPos.x, y - _bubble_status.lastTpPos.y);

            _bubble_status.offsetPos.x = _bubble_status.offsetPos.x + x - _bubble_status.lastTpPos.x;
            _bubble_status.offsetPos.y = _bubble_status.offsetPos.y + y - _bubble_status.lastTpPos.y;

            _bubble_status.lastTpPos.x = x;
            _bubble_status.lastTpPos.y = y;
        }




        void Launcher_Bubble::bubbleUpdate()
        {


            printf("%d %d\n", _bubble_status.offsetPos.x, _bubble_status.offsetPos.y);



            // lv_canvas_fill_bg(_data.screenCanvas, lv_color_hex(0x232323), 255);






            int x = 0;
            int y = 0;
            bool is_long = false;
            
            

            for (int i = 0; i < 32; i++) {
                

                lv_obj_t* img = lv_img_create(_data.screenMain);
                lv_img_set_src(img, &ui_img_icon_hdpi_default_png);
                

                if (!is_long) {
                    // lv_canvas_draw_img(_data.screenCanvas, _bubble_status.offsetPos.x + x + _bubble_cfg.iconSpaceX / 2 + _bubble_cfg.iconXoffset, _bubble_status.offsetPos.y + y + _bubble_cfg.iconYoffset, &ui_img_icon_hdpi_default_png, &_data.iconDsc);
                    
                    lv_obj_set_pos(img, _bubble_status.offsetPos.x + x + _bubble_cfg.iconSpaceX / 2 + _bubble_cfg.iconXoffset, _bubble_status.offsetPos.y + y + _bubble_cfg.iconYoffset);

                }
                else {
                    // lv_canvas_draw_img(_data.screenCanvas, _bubble_status.offsetPos.x + x + _bubble_cfg.iconXoffset, _bubble_status.offsetPos.y + y + _bubble_cfg.iconYoffset, &ui_img_icon_hdpi_default_png, &_data.iconDsc);
                
                    
                    lv_obj_set_pos(img, _bubble_status.offsetPos.x + x + _bubble_cfg.iconXoffset, _bubble_status.offsetPos.y + y + _bubble_cfg.iconYoffset);
                }
                



                x += _bubble_cfg.iconSpaceX;

                if (!is_long && ((x / _bubble_cfg.iconSpaceX) >= (_bubble_cfg.iconColMax - 1))) {
                    is_long = true;
                    x = 0;
                    y += _bubble_cfg.iconSpaceY;
                }
                else if (is_long && ((x / _bubble_cfg.iconSpaceX) >= _bubble_cfg.iconColMax)) { 
                    is_long = false;
                    x = 0;
                    y += _bubble_cfg.iconSpaceY;
                }

            }
        }


        void* Launcher_Bubble::_buffer_malloc(lv_coord_t w, lv_coord_t h)
        {
            return malloc(LV_CANVAS_BUF_SIZE_TRUE_COLOR(w, h) * sizeof(lv_color_t));
        }



        void Launcher_Bubble::onSetup()
        {
            setAppName("Launcher");
            setAllowBgRunning(true);

            /* Get framework control */
            _framework = (Framework*)getUserData();
        }


        /* Life cycle */
        void Launcher_Bubble::onCreate()
        {
            printf("[%s] onCreate\n", getAppName().c_str());

            /* Get hardware infos from database */
            _data.dispHor = (int16_t*)getDatabase()->Get(MC_DISP_HOR)->addr;
            _data.dispVer = (int16_t*)getDatabase()->Get(MC_DISP_VER)->addr;

            /* Get display mode */
            if (*_data.dispHor < *_data.dispVer) {
                _data.dispModePortrait = true;
            }

            /* Crete main screen */
            _data.screenMain = lv_obj_create(NULL);
            lv_obj_clear_flag(_data.screenMain, LV_OBJ_FLAG_SCROLL_CHAIN);






            /* Create canvas */
            // _data.screenCanvas = lv_canvas_create(_data.screenMain);
            // _data.canvasBuffer = (lv_color_t*)_buffer_malloc(*_data.dispHor, *_data.dispVer);
            // lv_canvas_set_buffer(_data.screenCanvas, _data.canvasBuffer, *_data.dispHor, *_data.dispVer, LV_IMG_CF_TRUE_COLOR_ALPHA);
            // lv_obj_center(_data.screenCanvas);
            // lv_obj_add_event_cb(_data.screenMain, _lvgl_event_cb, LV_EVENT_ALL, this);





            // lv_draw_img_dsc_t shit;
            // lv_draw_img_dsc_init(&shit);

            // lv_draw_img_dsc_init(&_data.iconDsc);
            

            // lv_canvas_fill_bg(_data.screenCanvas, lv_color_hex(0x232323), 255);
            // lv_canvas_draw_img(_data.screenCanvas, 0, 0, &ui_img_icon_hdpi_default_png, &shit);



            

            
        }


        void Launcher_Bubble::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());


            
            /* Load main screen and delete last one */
            if (lv_scr_act() != _data.screenMain) {
                lv_scr_load_anim(_data.screenMain, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, true);
            }

            bubbleUpdate();

        }


        void Launcher_Bubble::onRunning()
        {
            // printf("[%s] onRunning\n", getAppName().c_str());

            

   

            

            
        }


        void Launcher_Bubble::onRunningBG()
        {
            // printf("[%s] onRunningBG\n", getAppName().c_str());

            // printf("%d\n", _framework->isAnyAppRunningFG());

            /* If no App is running on foreground */
            if (!_framework->isAnyAppRunningFG()) {
                _framework->startApp(this);
            }



        }


        void Launcher_Bubble::onPause()
        {
            printf("[%s] onPause\n", getAppName().c_str());
        }


        void Launcher_Bubble::onDestroy()
        {
            printf("[%s] onDestroy\n", getAppName().c_str());
        }


    }
}
