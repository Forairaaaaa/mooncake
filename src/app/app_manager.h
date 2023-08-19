/**
 * @file app_manager.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.2
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "app_register.h"
#include <vector>


namespace MOONCAKE
{
    /* App manager */
    /* This class control app's opening, running or closing */
    /* It inherit from APP_Register, so we know what apps do we have */
    class APP_Manager : public APP_Register
    {
        public:
            /* This enum describe an app's current status of lifecycle */
            enum AppLifecycleState_t
            {
                ON_CREATE = 0,
                ON_RESUME,
                ON_RUNNING,
                ON_RUNNING_BG,
                ON_PAUSE,
                ON_DESTROY
            };

            /* A app lifecycle container */
            /* Holds an app and it's lifecycle status */
            struct AppLifecycle_t
            {
                APP_BASE* app = nullptr;
                AppLifecycleState_t state = ON_CREATE;
            };


        private:
            /* A list of apps' lifecycle */
            std::vector<AppLifecycle_t> _app_lifecycle_list;
            int _search_app_lifecycle_list(APP_BASE* app);


        public:
            /* API for app running control */

            /**
             * @brief Create an app
             * 
             * @param appPacker app's packer
             * @return APP_BASE* started app's pointer
             */
            APP_BASE* createApp(APP_PACKER_BASE* appPacker);

            /**
             * @brief Start an app, this method will only change passing app's state
             * 
             * @param app 
             * @return true 
             * @return false 
             */
            bool startApp(APP_BASE* app);

            /**
             * @brief Close an app, this method will only change passing app's state
             * 
             * @param app App's pointer which you want to close 
             * @return true 
             * @return false 
             */
            bool closeApp(APP_BASE* app);

            /**
             * @brief Update app manager's FSM, so the running apps' lifecycle methods can be called
             * 
             */
            void update();

            /**
             * @brief Destroy an app, app will be deleted by it's app packer
             * 
             * @param app App's pointer which you want to destroy 
             * @return true 
             * @return false 
             */
            bool destroyApp(APP_BASE* app);


    };      
}
