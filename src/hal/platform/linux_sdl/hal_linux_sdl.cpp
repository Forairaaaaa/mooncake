/**
 * @file hal_linux_sdl.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "hal_linux_sdl.h"
#include "../../lvgl/lvgl.h"
#include "sdl/lv_sdl_keyboard.h"
#include "sdl/lv_sdl_mouse.h"
#include "sdl/lv_sdl_mousewheel.h"
#include "sdl/lv_sdl_window.h"


namespace MOONCAKE {


    bool HAL_Linux_SDL::init()
    {
        if (!isDatabaseSet()) {
            printf("> database error\n");
            return false;
        }

        _database_init();
        _lvgl_init();
        
        return true;
    }


    void HAL_Linux_SDL::_lvgl_init()
    {
        printf("> init lvgl sdl\n");


        /*Initialize LVGL*/
        lv_init();

        /*Create a default group for keyboard navigation*/
        lv_group_set_default(lv_group_create());


        /*Initialize the HAL (display, input devices, tick) for LVGL*/
        lv_disp_t * disp = lv_sdl_window_create(
            _database->Get("DIS_HOR")->value<uint16_t>(),
            _database->Get("DIS_VER")->value<uint16_t>()
            );
        lv_indev_t * mouse = lv_sdl_mouse_create();
        lv_indev_set_group(mouse, lv_group_get_default());
        lv_indev_set_disp(mouse, disp);
        lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
        lv_indev_set_disp(mousewheel, disp);
        lv_indev_set_group(mousewheel, lv_group_get_default());
        lv_indev_t * keyboard = lv_sdl_keyboard_create();
        lv_indev_set_disp(keyboard, disp);
        lv_indev_set_group(keyboard, lv_group_get_default());

    }



    void HAL_Linux_SDL::_database_init()
    {
        _database->Add<uint16_t>("DIS_HOR", _config.dis_hor_res);
        _database->Add<uint16_t>("DIS_VER", _config.dis_ver_res);
        


    }






    void HAL_Linux_SDL::update()
    {
        // printf("> hal update\n");
        lv_timer_handler();
    }




}

