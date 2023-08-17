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
#include "../simplekv/simplekv.h"


namespace MOONCAKE
{   
    /* App base class */
    /* Contains states for life cycle control */
    /* Polymorphic life cycle makes different app */
    class APP_BASE
    {
        private:
            void* _user_data;
            bool _allow_bg_running;
            bool _go_close;
            bool _go_destroy;
            SIMPLEKV::SimpleKV* _database;


        protected:
            /* App internal API */

            /**
             * @brief Set if is App running background after closed
             * 
             * @param allow 
             */
            inline void setAllowBgRunning(bool allow) { _allow_bg_running = allow; }

            /**
             * @brief Close App 
             * 
             */
            inline void closeApp() { _go_close = true; }

            /**
             * @brief Destroy App, not going background
             * 
             */
            inline void destroyApp() { _go_destroy = true; }

            /**
             * @brief Get database
             * 
             * @return SIMPLEKV::SimpleKV* 
             */
            inline SIMPLEKV::SimpleKV* getDatabase() { return _database; }

            /**
             * @brief Get user data
             * 
             * @return void* 
             */
            inline void* getUserData() { return _user_data; };


        public:
            APP_BASE() :
                _user_data(nullptr),
                _allow_bg_running(false),
                _go_close(false),
                _go_destroy(false),
                _database(nullptr)
                {}


            /* API for App manager */
            inline void setDatabase(SIMPLEKV::SimpleKV* db) { _database = db; }
            inline void setUserData(void* userData) { _user_data = userData; }

            
            /* Basic API */
            inline bool isAllowBgRunning() { return _allow_bg_running; }
            inline bool isGoingClose() { return _go_close; }
            inline bool isGoingDestroy() { return _go_destroy; }
            inline void resetGoingCloseFlag() { _go_close = false; }
            inline void resetGoingDestroyFlag() { _go_destroy = false; }


            /**
             * @brief Lifecycle callbacks for derived to override
             * 
             */
            /* Setup App configs, called when App "install()" */
            virtual void onSetup() {}

            /* Life cycle */
            virtual void onCreate() {}
            virtual void onResume() {}
            virtual void onRunning() {}
            virtual void onRunningBG() {}
            virtual void onPause() {}
            virtual void onDestroy() {}

    };


    /* App packer base */
    /* Contains the static elements of an app, like name, icon... */
    /* Also an app's memory allocation, freeing... */
    class APP_PACKER_BASE
    {
        public:

            /**
             * @brief Override and return app's name
             * 
             * @return std::string 
             */
            virtual std::string getAppName() { return ""; };

            /**
             * @brief Override and return app's icon pointer
             * 
             * @return void* 
             */
            virtual void* getAppIcon() { return nullptr; }

            /**
             * @brief Override and return a new app's pointer
             * 
             * @return APP_BASE* 
             */
            virtual APP_BASE* newApp() { return nullptr; }

            /**
             * @brief Override and delete the passing app 
             * 
             * @param app 
             */
            virtual void deleteApp(APP_BASE* app) {}

    };
}
