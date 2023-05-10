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
#include "../../system_data_def.h"

LV_IMG_DECLARE(ui_img_icon_hdpi_default_png);
LV_IMG_DECLARE(ui_img_icon_mdpi_default_png);


namespace MOONCAKE {
    namespace BUILTIN_APP {


        void Launcher::onSetup()
        {
            setAppName("Launcher");
            setAllowBgRunning(true);
            _framework = (Framework*)getUserData();

        }


        /* Life cycle */
        void Launcher::onCreate()
        {
            printf("[%s] onCreate\n", getAppName().c_str());



            /* Get hardware infos from database */
            _data.dispHor = (int16_t*)getDatabase()->Get(MC_DISP_HOR)->addr;
            _data.dispVer = (int16_t*)getDatabase()->Get(MC_DISP_VER)->addr;
            if (*_data.dispHor < *_data.dispVer) {
                _data.dispModePortrait = true;
            }
            printf("%d %d %d\n", *_data.dispHor, *_data.dispVer, _data.dispModePortrait);



            _data.screenMain = lv_obj_create(NULL);
            






            lv_obj_t * app_list_flex = lv_obj_create(_data.screenMain);
            lv_obj_set_size(app_list_flex, (lv_coord_t)*_data.dispHor, (lv_coord_t)*_data.dispVer);
            lv_obj_align(app_list_flex, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_flex_flow(app_list_flex, LV_FLEX_FLOW_ROW_WRAP);
            lv_obj_set_flex_align(app_list_flex, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
            lv_obj_add_flag(app_list_flex, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);


            



            for(int i = 0; i < 11; i++) {
                lv_obj_t * obj;
                lv_obj_t * label;




                // obj = lv_imgbtn_create(app_list_flex);

                // // lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_hdpi_default_png, NULL);
                // // lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icon_hdpi_default_png, NULL);
                // // lv_obj_set_width(obj, 108);
                // // lv_obj_set_height(obj, 108);

                // lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_mdpi_default_png, NULL);
                // lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_icon_mdpi_default_png, NULL);
                // lv_obj_set_width(obj, 72);
                // lv_obj_set_height(obj, 72);

                // lv_obj_set_align(obj, LV_ALIGN_CENTER);
                // lv_obj_set_style_img_recolor(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_PRESSED);
                // lv_obj_set_style_img_recolor_opa(obj, 50, LV_PART_MAIN | LV_STATE_PRESSED);







                // obj = lv_img_create(app_list_flex);
                // lv_obj_set_width(obj, 72);
                // lv_obj_set_height(obj, 72);
                // lv_img_set_src(obj, &ui_img_icon_mdpi_default_png);
                // // lv_img_set_zoom(obj, 128);


                obj = lv_img_create(app_list_flex);
                lv_obj_set_width(obj, 108);
                lv_obj_set_height(obj, 108);
                lv_img_set_src(obj, &ui_img_icon_hdpi_default_png);
                // lv_img_set_zoom(obj, 128);





        


            }



        }


        void Launcher::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());


            
            /* Load main screen and delete last one */
            if (lv_scr_act() != _data.screenMain) {
                lv_scr_load_anim(_data.screenMain, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, true);
            }

        }


        void Launcher::onRunning()
        {
            // printf("[%s] onRunning\n", getAppName().c_str());

            

            // _framework->closeApp(this);



            static uint32_t ticks = lv_tick_get();
            static uint16_t shit = 128;


            if ((lv_tick_get() - ticks) > 100) {


                shit++;
                if (shit > 512) {
                    shit = 128;
                } 


                

                ticks = lv_tick_get();
            }


            
        }


        void Launcher::onRunningBG()
        {
            // printf("[%s] onRunningBG\n", getAppName().c_str());


            // _framework->startApp(this);



        }


        void Launcher::onPause()
        {
            printf("[%s] onPause\n", getAppName().c_str());
        }


        void Launcher::onDestroy()
        {
            printf("[%s] onDestroy\n", getAppName().c_str());
        }


    }
}
