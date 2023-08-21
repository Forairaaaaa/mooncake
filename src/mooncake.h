/**
 * @file mooncake.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.2
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "app/app.h"
#include "app/app_register.h"
#include "app/app_manager.h"
#include "input_system/input_device_register.h"
#include "simplekv/simplekv.h"
#include "spdlog/include/spdlog/spdlog.h"
#include "mc_conf_internal.h"


namespace MOONCAKE
{
    /* <To do> simplify user data (better wrap) */
    class Mooncake;

    /* Structure that contains userdata */
    /* Will be passed to every running apps */
    /* You can inherit this to create your own userdata */
    struct APP_UserData_t
    {
        /* Simple Key-Value in memory database */
        /* If not set, framework will create a default one  */
        SIMPLEKV::SimpleKV* database = nullptr;

        /* Pointer to the list of input devices */
        InputDevice_Register* inputDeviceList = nullptr;

        /* Pointer to the list of installed apps (for launcher usage) */
        const std::vector<APP_PACKER_BASE*>* installedAppList = nullptr;

        /* Pointer to the app Manager (for launcher usage) */
        APP_Manager* appManager = nullptr;
    };


    /* Mooncake framework class */
    /* Inherit App Register to manager apps' install and uninstall */
    /* Contains a App Manager to control apps' lifecycles */
    class Mooncake : public APP_Register
    {
        private:
            /* Component Input system */
            InputDevice_Register _input_device_register;

            /* Component App manager */
            APP_Manager _app_manager;

            APP_UserData_t* _user_data;
            APP_PACKER_BASE* _boot_anim;
            void (*_database_setup_callback)(SIMPLEKV::SimpleKV*);

            /* Flag to free the memory, if they are created by framework */
            bool _flag_free_user_data;
            bool _flag_free_boot_anim;
            bool _flag_free_database;

            void _data_base_setup_internal();
        
        public:
            Mooncake() :
                _user_data(nullptr),
                _boot_anim(nullptr),
                _database_setup_callback(nullptr),
                _flag_free_user_data(false),
                _flag_free_boot_anim(false),
                _flag_free_database(false)
                {}
            ~Mooncake();

            /**
             * @brief Get the reference to the internal App manager 
             * 
             * @return APP_Manager& 
             */
            inline APP_Manager& appManager() { return _app_manager; }

            /**
             * @brief Get the reference to the internal Input device register
             * 
             * @return InputDevice_Register& 
             */
            inline InputDevice_Register& inputDeviceRegister() { return _input_device_register; }

            /**
             * @brief Set the user data, which will be passed to every apps
             * , if not set, framework will create a default one 
             * @param userData 
             */
            inline void setUserData(APP_UserData_t* userData) { _user_data = userData; }

            /**
             * @brief Get the User Data object
             * 
             * @return APP_UserData_t* 
             */
            inline APP_UserData_t* getUserData() { return _user_data; }

            /**
             * @brief Set the boot anim, which will be created and run in framework's init()
             * , if not set, framework will create a default one 
             * @param bootAnim 
             */
            inline void setBootAnim(APP_PACKER_BASE* bootAnim) { _boot_anim = bootAnim; }

            /**
             * @brief Set the Database Setup Callback
             * , the call back will be called after some basic data were set, you can add some custom data into database in the callback
             * @param databaseSetupCallback 
             */
            inline void setDatabaseSetupCallback(void (*databaseSetupCallback)(SIMPLEKV::SimpleKV*)) { _database_setup_callback = databaseSetupCallback; }

            /**
             * @brief Init framework
             * 
             */
            void init();

            /**
             * @brief Calling this to keep framework running 
             * 
             */
            void update();
    };
}
