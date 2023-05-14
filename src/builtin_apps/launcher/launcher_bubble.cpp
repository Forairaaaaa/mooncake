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

            if(code == LV_EVENT_PRESSING) {

                // printf("6\n");



                lv_point_t p;
                lv_indev_get_point(lv_indev_get_act(), &p);
                // printf("%d %d\n", p.x, p.y);



                Launcher_Bubble* launcher = (Launcher_Bubble*)lv_event_get_user_data(e);
                launcher->bubbleUpdate(p.x, p.y);
            }

        }




        void Launcher_Bubble::bubbleUpdate(lv_coord_t tpX, lv_coord_t tpY)
        {

            // printf("%d %d\n", tpX, tpY);




            printf("%d %d\n", tpX - _bubble_status.lastTpPos.x, tpY - _bubble_status.lastTpPos.y);

            _bubble_status.offsetPos.x = _bubble_status.offsetPos.x + tpX - _bubble_status.lastTpPos.x;
            _bubble_status.offsetPos.y = _bubble_status.offsetPos.y + tpY - _bubble_status.lastTpPos.y;

            _bubble_status.lastTpPos.x = tpX;
            _bubble_status.lastTpPos.y = tpY;








            lv_canvas_fill_bg(_data.screenCanvas, lv_color_hex(0x232323), 255);


            int x = 0;
            int y = 0;
            bool is_long = false;
            
            

            for (int i = 0; i < 20; i++) {
                
                

                if (!is_long) {
                    lv_canvas_draw_img(_data.screenCanvas, _bubble_status.offsetPos.x + x + _bubble_cfg.iconSpaceX / 2 + _bubble_cfg.iconXoffset, _bubble_status.offsetPos.y + y + _bubble_cfg.iconYoffset, &ui_img_icon_hdpi_default_png, &_data.iconDsc);
                }
                else {
                    lv_canvas_draw_img(_data.screenCanvas, _bubble_status.offsetPos.x + x + _bubble_cfg.iconXoffset, _bubble_status.offsetPos.y + y + _bubble_cfg.iconYoffset, &ui_img_icon_hdpi_default_png, &_data.iconDsc);
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






            /* Create canvas */
            _data.screenCanvas = lv_canvas_create(_data.screenMain);
            _data.canvasBuffer = (lv_color_t*)_buffer_malloc(*_data.dispHor, *_data.dispVer);
            lv_canvas_set_buffer(_data.screenCanvas, _data.canvasBuffer, *_data.dispHor, *_data.dispVer, LV_IMG_CF_TRUE_COLOR_ALPHA);
            lv_obj_center(_data.screenCanvas);
            lv_obj_add_event_cb(_data.screenMain, _lvgl_event_cb, LV_EVENT_ALL, this);





            // lv_draw_img_dsc_t shit;
            // lv_draw_img_dsc_init(&shit);

            lv_draw_img_dsc_init(&_data.iconDsc);
            

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

            bubbleUpdate(-1, -1);

        }


        void Launcher_Bubble::onRunning()
        {
            // printf("[%s] onRunning\n", getAppName().c_str());

            

            

            // lv_point_t tp;
            // lv_indev_get_point(lv_indev_get_act(), &tp);

            // printf("%d %d\n", tp.x, tp.y);




            // lv_indev_t * indev = lv_indev_get_act();
            // lv_point_t p;
            // lv_indev_get_vect(indev, &p);
            // printf("%d %d\n", p.x, p.y);

            // lv_group_t * g             = (lv_group_t*)lv_obj_get_group(_data.screenMain);
            // bool editing               = lv_group_get_editing(g);
            // printf("%d\n", (int)lv_indev_get_type(lv_indev_get_act()));



            // _bubble_update();

            
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
