/**
 * @file framework.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app/app_manager.h"


namespace MOONCAKE {


    struct FrameworkConfig_t {
        SIMPLEKV::SimpleKV* database = nullptr;
        APP_BASE* bootAnim = nullptr;
        APP_BASE* launcher = nullptr;

        bool playBootAnim = true;
    };


    class Framework : public APP_Manger {
        private:
            FrameworkConfig_t _config;
            bool _builtin_database;
            bool _builtin_launcher;

            bool _run_boot_anim();
            

        public:
            Framework() : 
                _builtin_database(true),
                _builtin_launcher(true) {}
            ~Framework() = default;


            /* Configs */
            inline void config(const FrameworkConfig_t& cfg) { _config = cfg; }
            inline FrameworkConfig_t config(void) { return _config; }
            inline void setDatabase(SIMPLEKV::SimpleKV* db) { _config.database = db; }
            inline void setBootAnim(APP_BASE* bootAnim) { _config.bootAnim = bootAnim; }
            inline void setLauncher(APP_BASE* luancher) { _config.launcher = luancher; }
            

            
            /* Framework init */
            bool init();


            /* Call this in loop to keep framework running */
            void update();

    };


}
