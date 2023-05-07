/**
 * @file app.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../simplekv/simplekv.h"


namespace MOONCAKE {


    /* Inherit and override "Life cycle" to create your own App */
    class APP_BASE {
        private:
            std::string _name;
            void* _user_data;
            void* _icon_addr;
            bool _allow_bg_running;
            bool _finished;
            SIMPLEKV::SimpleKV* _database;


        protected:
            /* App internal API */
            inline void setAppName(const std::string& name) { _name = name; }
            inline void setAppIcon(void* icon) { _icon_addr = icon; }
            inline SIMPLEKV::SimpleKV* Database() { return _database; }
            inline void* getUserData() { return _user_data; };
            inline void allowBackgroudRunning(bool allow) { _allow_bg_running = allow; }
            inline void endApp() { _finished = true; }


        public:
            APP_BASE() :
                _name(""),
                _user_data(nullptr),
                _icon_addr(nullptr),
                _allow_bg_running(false),
                _finished(false),
                _database(nullptr) {}
            ~APP_BASE() = default;


            /* Set database */
            inline void setDatabase(SIMPLEKV::SimpleKV* db) { _database = db; }


            /* Basic API */
            inline std::string getName() { return _name; }
            inline void* iconAddr() { return _icon_addr; }
            inline bool allowBgRunning() { return _allow_bg_running; }


            /* Life cycle */
            virtual void onCreate() {}
            virtual void onResume() {}
            virtual void onRunning() {}
            virtual void onPause() {}
            virtual void onDestroy() {}

    };


    struct APPList_t {
        APP_BASE* app = nullptr;
        uint16_t id = 0;
    };


    class APP_Register {
        private:
            std::vector<APPList_t> _app_list;

        public:
            APP_Register() {}
            ~APP_Register() = default;

            /* Basic API */
            bool install(APP_BASE* app, SIMPLEKV::SimpleKV* database, void* userData = nullptr);
            bool uninstall(APP_BASE* app);

            inline std::vector<APPList_t> getAppList() { return _app_list; }


    };


}
