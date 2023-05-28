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
#include <ArduinoJson.hpp>

/* If not include this, lv_fs acts strange in my wsl linux env */
#include <stdio.h>
#include <stdlib.h>


namespace MOONCAKE {
    namespace BUILTIN_APP {


        void WF_User_Custom::_lvgl_event_cb(lv_event_t* e)
        {
            /* Get event code */
            lv_event_code_t code = lv_event_get_code(e);

            /* Clicked */
            if (code == LV_EVENT_SHORT_CLICKED) {
                // printf("clicked\n");
                
                /* Set using face path */
                lv_obj_t* roller = lv_event_get_target(e);
                if ((const char*)lv_obj_get_user_data(roller) == "rl") {
                    
                    char string_buffer[256];
                    lv_roller_get_selected_str(roller, string_buffer, 256);

                    // printf("select %s\n", string_buffer);
                    WF_User_Custom* app = (WF_User_Custom*)lv_event_get_user_data(e);
                    app->_custom_data.wf_current_using_path = string_buffer;
                }

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


        bool WF_User_Custom::_choose_watch_face()
        {
            printf("[%s] choose face\n", getAppName().c_str());

            /* Open watch faces folder */
            lv_fs_dir_t dir;
            lv_fs_res_t res;
            res = lv_fs_dir_open(&dir, _custom_data.wf_folder_path);
            if (res != LV_FS_RES_OK) {
                printf("[%s] open %s failed %d\n", getAppName().c_str(), _custom_data.wf_folder_path, res);
                return false;
            }

            /* Read watch faces folders */
            char string_buffer[256];
            std::string wf_custom_path_list = "";
            while (1) {
                /* Open dir */
                res = lv_fs_dir_read(&dir, string_buffer);
                if (res != LV_FS_RES_OK) {
                    printf("[%s] read dir error %d\n", getAppName().c_str(), res);
                    return false;
                }
                if (strlen(string_buffer) == 0) {
                    break;
                }

                /* Add into list without '/' */
                wf_custom_path_list += (string_buffer + 1);
                wf_custom_path_list += "\n";
            }
            /* Remove extra \n */
            wf_custom_path_list = wf_custom_path_list.substr(0, wf_custom_path_list.size() - 1);
            printf("%s\n", wf_custom_path_list.c_str());

            /* Close folder */
            lv_fs_dir_close(&dir);


            /* Create a roller as selector */
            _data.roller = lv_roller_create(_data.screen);
            lv_roller_set_options(_data.roller, wf_custom_path_list.c_str(), LV_ROLLER_MODE_NORMAL);
            lv_roller_set_visible_row_count(_data.roller, 4);
            lv_obj_center(_data.roller);
            lv_obj_add_event_cb(_data.roller, _lvgl_event_cb, LV_EVENT_ALL, (void*)this);
            lv_obj_set_user_data(_data.roller, (void*)"rl");

            
            return true;
        }


        void WF_User_Custom::_create_watch_face()
        {
            /* Get description */
            std::string buffer;
            buffer = _custom_data.wf_folder_path;
            buffer += "/";
            buffer += _custom_data.wf_current_using_path;
            buffer += "/";
            buffer += _custom_data.wf_custom_description_path;
            printf("[%s] read desc: %s\n", getAppName().c_str(), buffer.c_str());

            /* Read description */
            lv_fs_file_t desc;
            lv_fs_res_t res = lv_fs_open(&desc, buffer.c_str(), LV_FS_MODE_WR);
            if(res != LV_FS_RES_OK) {
                printf("[%s] error: %d\n", getAppName().c_str(), res);
                return;
            }



            /* Close description */
            lv_fs_close(&desc);


            /* Delect roller */
            lv_obj_del(_data.roller);

        }


        void WF_User_Custom::onSetup()
        {
            setAppName("Cutom Watch Face");
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


            /* Select watch face */
            if (!_choose_watch_face()) {
                destroyApp();
            }

        }


        void WF_User_Custom::onResume()
        {
            printf("[%s] onResume\n", getAppName().c_str());
        }


        void WF_User_Custom::onRunning()
        {
            /* If is all setup */
            if (_data.running) {

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
            else {
                
                /* If watch face selected */
                if (_custom_data.wf_current_using_path != "null") {
                    _data.running = true;
                    _create_watch_face();
                }

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

