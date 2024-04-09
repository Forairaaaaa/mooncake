/**
 * @file app.h
 * @author Forairaaaaa
 * @brief
 * @version 0.2
 * @date 2023-08-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <string>

namespace MOONCAKE
{
    /* -------------------------------------------------------------------------- */
    /*                               App packer base                              */
    /* -------------------------------------------------------------------------- */
    // A base class to handle an app's create and destroy (factory)
    // Also contains commom static asset like name, icon pointer ..
    class APP_PACKER_BASE
    {
    private:
        void* _framework;

    public:
        APP_PACKER_BASE() : _framework(nullptr) {}
        virtual ~APP_PACKER_BASE() {}

        // Framework pointer
        inline void setFramwork(void* userData) { _framework = userData; }
        inline void* getFramwork() { return _framework; }

        // Self pointer
        inline APP_PACKER_BASE* getAddr() { return this; }

        /* ------------------------------- App factory ------------------------------ */
    public:
        /**
         * @brief Override and return a new app's pointer
         *
         * @return void* new app's pointer
         */
        virtual void* newApp() { return nullptr; }

        /**
         * @brief Override and delete the passing app
         *
         * @param app app's pointer
         */
        virtual void deleteApp(void* app) {}

        /* -------------------------- Basic app static data ------------------------- */
    public:
        /**
         * @brief Override and return app's name
         *
         * @return const std::string
         */
        virtual const std::string getAppName() { return ""; };

        /**
         * @brief Override and return app's icon pointer
         *
         * @return void*
         */
        virtual void* getAppIcon() { return nullptr; }

        /**
         * @brief Override and return more custom data, like theme color, iamges...
         *
         * @return void*
         */
        virtual void* getCustomData() { return nullptr; }
    };

    /* -------------------------------------------------------------------------- */
    /*                                  App base                                  */
    /* -------------------------------------------------------------------------- */
    // A base class that contains an app's life cycle hooks
    // Also internal states for app manager's life cycle handling
    class APP_BASE
    {
    private:
        APP_PACKER_BASE* _app_packer;

        // Internal state
        struct State_t
        {
            bool allow_bg_running = false;
            bool go_start = false;
            bool go_close = false;
            bool go_destroy = false;
        };
        State_t _state;

    public:
        APP_BASE() : _app_packer(nullptr) {}
        virtual ~APP_BASE() {}

        /* -------------------- static asset getting and setting -------------------- */
    public:
        inline void setAppPacker(APP_PACKER_BASE* appPacker) { _app_packer = appPacker; }
        inline APP_PACKER_BASE* getAppPacker() { return _app_packer; }
        inline std::string getAppName() { return getAppPacker()->getAppName(); }
        inline void* getAppIcon() { return getAppPacker()->getAppIcon(); }
        inline void* getCustomData() { return getAppPacker()->getCustomData(); }
        inline void* getFramwork() { return getAppPacker()->getFramwork(); }

        /* --------------------------- State getting apis --------------------------- */
    public:
        inline bool isAllowBgRunning() { return _state.allow_bg_running; }
        inline bool isGoingStart() { return _state.go_start; }
        inline bool isGoingClose() { return _state.go_close; }
        inline bool isGoingDestroy() { return _state.go_destroy; }
        inline void resetGoingStartFlag() { _state.go_start = false; }
        inline void resetGoingCloseFlag() { _state.go_close = false; }
        inline void resetGoingDestroyFlag() { _state.go_destroy = false; }

        /* --------------- Apis to controls lifecycle inside your app --------------- */
    protected:
        /**
         * @brief Set if is App running background after closed
         *
         * @param allow
         */
        inline void setAllowBgRunning(bool allow) { _state.allow_bg_running = allow; }

        /**
         * @brief Notice the app manager, that this app want to be started
         *
         */
        inline void startApp() { _state.go_start = true; }

        /**
         * @brief Notice the app manager, that this app want to be cloesd
         * , better call this in onRunning() only, to avoid repeat method callback
         */
        inline void closeApp() { _state.go_close = true; }

        /**
         * @brief Notice the app manager, that this app want to be destroyed
         * , better call this in onRunning() or onRunningBG() only, to avoid repeat method callback
         */
        inline void destroyApp() { _state.go_destroy = true; }

        /* ----------------------------- Lifecycle hooks ---------------------------- */
    public:
        // Override hook functions to fit your need
        // It's like very lite version of andriod's lifecycle
        // https://developer.android.com/guide/components/activities/activity-lifecycle
        virtual void onCreate() {}
        virtual void onResume() {}
        virtual void onRunning() {}
        virtual void onRunningBG() {}
        virtual void onPause() {}
        virtual void onDestroy() {}
    };
} // namespace MOONCAKE
