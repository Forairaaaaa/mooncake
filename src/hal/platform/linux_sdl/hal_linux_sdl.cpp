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


namespace MOONCAKE {


    void HAL_Linux_SDL::_lvgl_init()
    {

    }


    bool HAL_Linux_SDL::init()
    {
        if (!isDatabaseSet()) {
            printf("database error\n");
            return false;
        }
        _lvgl_init();
        return true;
    }

}

