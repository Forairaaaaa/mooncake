/**
 * @file wf_user_custom.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../app/app.h"
#include "../../system_data_def.h"
#include <lvgl.h>


namespace MOONCAKE {
    namespace BUILTIN_APP {


        namespace WF_USER_CUSTOM {

            struct Data_t {
                /* Update data in 1Hz */
                uint32_t update_interval = 1000;
                uint32_t update_count = 0;

                lv_obj_t* screen = nullptr;
                lv_obj_t* img_bg_static = nullptr;
                lv_obj_t* img_bk_gif = nullptr;
                lv_obj_t* img_clock_hour_a = nullptr;
                lv_obj_t* img_clock_hour_b = nullptr;
                lv_obj_t* img_clock_colon = nullptr;
                lv_obj_t* img_clock_min_a = nullptr;
                lv_obj_t* img_clock_min_b = nullptr;

                DataTime_t* time_ptr = nullptr;
                bool* just_wake_up_ptr = nullptr;
                bool* key_pwr_home_ptr = nullptr;
            };

        }


        class WF_User_Custom : public APP_BASE {
            private:
                WF_USER_CUSTOM::Data_t _data;

                static void _lvgl_event_cb(lv_event_t* e);
                void _update_data();


            public:
                WF_User_Custom() = default;
                ~WF_User_Custom() = default;


                /**
                 * @brief Lifecycle callbacks for derived to override
                 * 
                 */
                /* Setup App configs, called when App "install()" */
                void onSetup();

                /* Life cycle */
                void onCreate();
                void onResume();
                void onRunning();
                void onRunningBG();
                void onPause();
                void onDestroy();
            
        };


    }
}
