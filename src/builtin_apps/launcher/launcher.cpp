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
            






            lv_obj_t * cont_row = lv_obj_create(_data.screenMain);
            lv_obj_set_size(cont_row, (lv_coord_t)*_data.dispHor, (lv_coord_t)*_data.dispVer);
            lv_obj_align(cont_row, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_flex_flow(cont_row, LV_FLEX_FLOW_ROW_WRAP);
            lv_obj_set_flex_align(cont_row, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
            lv_obj_add_flag(cont_row, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);


            



            for(int i = 0; i < 11; i++) {
                lv_obj_t * obj;
                lv_obj_t * label;

                /*Add items to the row*/
                obj = lv_btn_create(cont_row);
                lv_obj_set_size(obj, LV_PCT(36), LV_SIZE_CONTENT);
                lv_obj_set_style_radius(obj, 36, LV_PART_MAIN | LV_STATE_DEFAULT);

                label = lv_label_create(obj);
                lv_label_set_text_fmt(label, "Item: %d", i);
                lv_obj_center(label);

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
