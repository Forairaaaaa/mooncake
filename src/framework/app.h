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
        protected:
            std::string _name;
            void* _icon_addr;
            bool _allow_bg_running;
            bool _finished;
            SIMPLEKV::SimpleKV* _database;

            /* App internal API */
            inline SIMPLEKV::SimpleKV* Database() { return _database; }
            inline void endApp() { _finished = true; }


        public:
            APP_BASE() : _name(""), _icon_addr(nullptr), _allow_bg_running(false), _finished(false), _database(nullptr) {}
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


}
