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


namespace MOONCAKE {


    bool HAL_Linux_SDL::init()
    {
        if (!isDatabaseSet()) {
            printf("> database error\n");
            return false;
        }
        _lvgl_init();
        return true;
    }


    void HAL_Linux_SDL::_lvgl_init()
    {
        printf("> init lvgl sdl\n");


        /*Initialize LVGL*/
        lv_init();

        // /*Create a default group for keyboard navigation*/
        // lv_group_set_default(lv_group_create());

        // /* Display init */
        // lv_disp_t * disp = lv_sdl_window_create(448, 328);
        // lv_indev_t * mouse = lv_sdl_mouse_create();
        // lv_indev_set_group(mouse, lv_group_get_default());
        // lv_indev_set_disp(mouse, disp);

        // // LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
        // // lv_obj_t * cursor_obj;
        // // cursor_obj = lv_img_create(lv_scr_act());         /*Create an image object for the cursor */
        // // lv_img_set_src(cursor_obj, &mouse_cursor_icon);   /*Set the image source*/
        // // lv_indev_set_cursor(mouse, cursor_obj);           /*Connect the image  object to the driver*/

        // lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
        // lv_indev_set_disp(mousewheel, disp);
        // lv_indev_set_group(mousewheel, lv_group_get_default());

        // lv_indev_t * keyboard = lv_sdl_keyboard_create();
        // lv_indev_set_disp(keyboard, disp);
        // lv_indev_set_group(keyboard, lv_group_get_default());



    }


    void HAL_Linux_SDL::update()
    {
        // printf("> hal update\n");
        lv_timer_handler();
    }

}

