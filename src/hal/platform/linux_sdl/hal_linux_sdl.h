/**
 * @file hal_linux_sdl.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 * https://github.com/lvgl/lv_port_pc_eclipse/tree/master 
 * 
 */
#pragma once
#include "../../hal.hpp"


namespace MOONCAKE {


    class HAL_Linux_SDL : public HAL_BASE {
        private:
            void _lvgl_init();
            void _database_init();

        public:
            /* Init database */
            HAL_Linux_SDL() { _database = new SIMPLEKV::SimpleKV; }
            ~HAL_Linux_SDL() = default;

            /* Init override */
            bool init();

            /* Update override */
            void update();

    };


}

