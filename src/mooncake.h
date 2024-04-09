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
#include "app/app_manager.h"
#include "app/app_register.h"
#include "types.h"

/* Disable some features */
#ifdef ESP_PLATFORM
#define SPDLOG_NO_EXCEPTIONS
#define SPDLOG_NO_THREAD_ID
#endif
#include "spdlog/include/spdlog/spdlog.h"

namespace MOONCAKE
{
    /* -------------------------------------------------------------------------- */
    /*                                  Mooncake                                  */
    /* -------------------------------------------------------------------------- */
    // A class to provide app frmework apis
    class Mooncake
    {
    private:
        // Components
        struct Data_t
        {
            APP_Register* app_register = nullptr;
            APP_Manager* app_manager = nullptr;
        };
        Data_t _data;
        void _free_data();
        void _init_log();

    public:
        ~Mooncake();

        /* ---------------------------- Components getter --------------------------- */
    public:
        inline APP_Register* getAppRegister() { return _data.app_register; }
        inline APP_Manager* getAppManager() { return _data.app_manager; }

        /* ----------------------------- Framework apis ----------------------------- */
    public:
        /**
         * @brief Init framework
         *
         */
        void init();

        /**
         * @brief Calling this in loop to keep framework running
         *
         */
        void update();

        /**
         * @brief Install an app (Register an app packer)
         *
         * @param appPacker
         * @return true
         * @return false
         */
        inline bool installApp(APP_PACKER_BASE* appPacker) { return _data.app_register->install(appPacker, this); }

        /**
         * @brief Uninstall an app (Remove it from the register)
         *
         * @param appPacker
         * @return true
         * @return false
         */
        inline bool uninstallApp(APP_PACKER_BASE* appPacker) { return _data.app_register->uninstall(appPacker); }

        /**
         * @brief Uninstall all apps
         *
         */
        inline void uninstallAllApps() { _data.app_register->uninstallAllApps(); }

        /**
         * @brief Get the total installed app num in app register
         *
         * @return std::size_t
         */
        inline std::size_t getInstalledAppNum() { return _data.app_register->getInstalledAppNum(); }

        /**
         * @brief Get the reference to the installed app packer list
         *
         * @return std::vector<APP_PACKER_BASE*>&
         */
        inline std::vector<APP_PACKER_BASE*>& getInstalledAppList() { return _data.app_register->getInstalledAppList(); }

        /* Framework wrap to the App manager */

        /**
         * @brief Create an app
         *
         * @param appPacker app's packer
         * @return APP_BASE* started app's pointer
         */
        inline APP_BASE* createApp(APP_PACKER_BASE* appPacker) { return _data.app_manager->createApp(appPacker); }

        /**
         * @brief Start an app, this method will only change passing app's state
         *
         * @param app
         * @return true
         * @return false
         */
        inline bool startApp(APP_BASE* app) { return _data.app_manager->startApp(app); }

        /**
         * @brief Wrap of create and start an app
         *
         * @param appPacker
         * @return true
         * @return false
         */
        inline bool createAndStartApp(APP_PACKER_BASE* appPacker) { return startApp(createApp(appPacker)); }

        /**
         * @brief Close an app, this method will only change passing app's state
         *
         * @param app App's pointer which you want to close
         * @return true
         * @return false
         */
        inline bool closeApp(APP_BASE* app) { return _data.app_manager->closeApp(app); }

        /**
         * @brief Destroy an app, app will be deleted by it's app packer
         *
         * @param app App's pointer which you want to destroy
         * @return true
         * @return false
         */
        inline bool destroyApp(APP_BASE* app) { return _data.app_manager->destroyApp(app); }

        /**
         * @brief Destroy all apps
         *
         */
        inline void destroyAllApps() { _data.app_manager->destroyAllApps(); }

        /**
         * @brief Get total created app num in app manager
         *
         * @return std::size_t
         */
        inline std::size_t getCreatedAppNum() { return _data.app_manager->getCreatedAppNum(); }
    };
} // namespace MOONCAKE
