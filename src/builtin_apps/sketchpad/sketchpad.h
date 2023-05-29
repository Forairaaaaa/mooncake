/**
 * @file sketchpad.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-29
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


        namespace SKETCHPAD {

            struct Data_t {

                lv_obj_t* screen = nullptr;

                bool* key_pwr_home_ptr = nullptr;
                
            };

        }


        class Sketchpad : public APP_BASE {
            private:
                SKETCHPAD::Data_t _data;

                static void _lvgl_event_cb(lv_event_t* e);


            public:
                Sketchpad() = default;
                ~Sketchpad() = default;


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

