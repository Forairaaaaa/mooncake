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


namespace MOONCAKE {
    namespace BUILTIN_APP {


        void Launcher::_lvgl_event_cb(lv_event_t* e)
        {
            /* Get event code */
            lv_event_code_t code = lv_event_get_code(e);

            if(code == LV_EVENT_SHORT_CLICKED) {
                /* Get framework pointer */
                Framework* framework = (Framework*)lv_event_get_user_data(e);
                /* Get App pointer */
                APP_BASE* app = (APP_BASE*)lv_obj_get_user_data(lv_event_get_target_obj(e));
                /* Start App */
                framework->startApp(app);
            }

            else if (code == LV_EVENT_PRESSED) {
                /* If pressed, smaller Icon */
                lv_img_set_zoom(lv_event_get_target_obj(e), lv_img_get_zoom(lv_event_get_target_obj(e)) - 10);
            }

            else if (code == LV_EVENT_RELEASED) {
                /* If released, set it back */
                lv_img_set_zoom(lv_event_get_target_obj(e), lv_img_get_zoom(lv_event_get_target_obj(e)) + 10);
            }

            else if (code == LV_EVENT_LONG_PRESSED) {
                /* Get App pointer */
                APP_BASE* app = (APP_BASE*)lv_obj_get_user_data(lv_event_get_target_obj(e));
                // printf("%s\n", app->getAppName().c_str());

                /* Draw a message box to show App infos */
                static const char * btns[] = {""};
                std::string app_infos;
                app_infos = "Name:   " + app->getAppName() + "\nAllow BG running:   ";
                if (app->isAllowBgRunning()) {
                    app_infos += "Yes";
                }
                else {
                    app_infos += "No";
                }
                lv_obj_t * mbox1 = lv_msgbox_create(NULL, "App infos", app_infos.c_str(), btns, true);
                lv_obj_center(mbox1);
            }

            /* If scrolling, zoom Apps' Icon */
            else if (code == LV_EVENT_SCROLL) {
                /* Get launcher pointer */
                Launcher* launcher = (Launcher*)lv_event_get_user_data(e);
                launcher->updateAppIconZoom();
            }

        }


        void Launcher::updateAppIconZoom()
        {
            /* Zoom the Icons when reach edge */
            lv_coord_t scroll_bar_y = lv_obj_get_scroll_y(_data.appFlexCntr);
            lv_coord_t zoom_area_half_height = *_data.dispVer / 4;
            lv_coord_t zoom_area_edge_t = scroll_bar_y + *_data.dispVer / 4;
            lv_coord_t zoom_area_edge_m = scroll_bar_y + *_data.dispVer / 2;
            lv_coord_t zoom_area_edge_b = scroll_bar_y + *_data.dispVer / 4 * 3;
            lv_coord_t icon_y = 0;
            int icon_zoom = LV_ZOOM_NONE;
            
            /* Iterate all Icons */
            for (int i = 0; i < lv_obj_get_child_cnt(_data.appFlexCntr); i++) {
                /* Update Icon y */
                icon_y = lv_obj_get_y2(lv_obj_get_child(_data.appFlexCntr, i));
                /* If at not zoom area */
                if ((icon_y >= zoom_area_edge_t) && (icon_y <= zoom_area_edge_b)) {
                    /* Zoom to normal */
                    icon_zoom = LV_ZOOM_NONE;
                }
                else {
                    /* Get how far Icon is out of edge */
                    icon_zoom = abs(icon_y - zoom_area_edge_m) - zoom_area_half_height;
                    /* Smaller it */
                    icon_zoom = LV_ZOOM_NONE - icon_zoom;
                    /* If hit limit */
                    if (icon_zoom < 32) {
                        icon_zoom = 32;
                    }
                }
                /* Set zoom */
                lv_img_set_zoom(lv_obj_get_child(_data.appFlexCntr, i), icon_zoom);
            }
        }


        void Launcher::_update_app_list()
        {
            /* Delete old container */
            if (_data.appFlexCntr != nullptr) {
                lv_obj_del(_data.appFlexCntr);
            }

            /* Create a flex container for App list */
            _data.appFlexCntr = lv_obj_create(_data.screenMain);
            lv_obj_set_size(_data.appFlexCntr, (lv_coord_t)*_data.dispHor, (lv_coord_t)*_data.dispVer);
            lv_obj_align(_data.appFlexCntr, LV_ALIGN_CENTER, 0, 0);
            /* Set background */
            lv_obj_set_style_bg_opa(_data.appFlexCntr, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(_data.appFlexCntr, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            /* Set scroll bar */
            lv_obj_add_flag(_data.appFlexCntr, LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);
            lv_obj_set_scrollbar_mode(_data.appFlexCntr, LV_SCROLLBAR_MODE_OFF);
            /* Setup flex configs */
            lv_obj_set_flex_flow(_data.appFlexCntr, LV_FLEX_FLOW_ROW_WRAP);
            lv_obj_set_flex_align(_data.appFlexCntr, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_START);
            /* Add event callback */
            lv_obj_add_event(_data.appFlexCntr, _lvgl_event_cb, LV_EVENT_SCROLL, (void*)this);

            /* Put App into list */
            for (auto i : _framework->getAppList()) {
                /* If is launcher */
                if (i.app == this) {
                    continue;
                }

                /* Create a object */
                lv_obj_t* app = lv_img_create(_data.appFlexCntr);

                /* If App Icon not set, use default */
                if (i.app->getAppIcon() == nullptr) {
                    lv_img_set_src(app, &ui_img_icon_hdpi_default_png);
                }
                else {
                    lv_img_set_src(app, i.app->getAppIcon());
                }

                lv_obj_set_width(app, ui_img_icon_hdpi_default_png.header.w);
                lv_obj_set_height(app, ui_img_icon_hdpi_default_png.header.h);

                /* Set App pointer as user data */
                lv_obj_set_user_data(app, (void*)i.app);
                
                /* Add event callback */
                lv_obj_add_flag(app, LV_OBJ_FLAG_CLICKABLE);
                lv_obj_set_style_img_recolor(app, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_PRESSED);
                lv_obj_set_style_img_recolor_opa(app, 50, LV_PART_MAIN | LV_STATE_PRESSED);
                lv_obj_add_event(app, _lvgl_event_cb, LV_EVENT_ALL, (void*)_framework);
            }

            /* Hit event to update zoom once */
            lv_obj_scroll_to_y(_data.appFlexCntr, 1, LV_ANIM_OFF);
        }


        void Launcher::onSetup()
        {
            setAppName("Launcher");
            setAllowBgRunning(true);

            /* Get framework control */
            _framework = (Framework*)getUserData();
        }


        /* Life cycle */
        void Launcher::onCreate()
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
            // lv_obj_set_style_bg_color(_data.screenMain, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);

            /* Update app list */
            _update_app_list();
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

            // printf("%d\n", _framework->isAnyAppRunningFG());

            /* If no App is running on foreground */
            if (!_framework->isAnyAppRunningFG()) {
                _framework->startApp(this);
            }



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
