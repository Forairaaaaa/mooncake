/**
 * @file app_manager.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "app_register.h"


namespace MOONCAKE {


    struct APPRunning_t {
        APP_BASE* app = nullptr;
        bool isOnFG = false;
        bool allowRunningBG = false;
    };


    class APP_Manger : public APP_Register {
        private:
            std::vector<APPRunning_t> _running_apps;


        public:
            APP_Manger() = default;
            ~APP_Manger() = default;


            /* Basic API */
            bool startApp(int id);
            bool startApp(const char* name);
            bool closeApp(int id);
            bool closeApp(const char* name);


            /* Call this in loop to update App running */
            void update();

    };


}
