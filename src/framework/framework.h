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
        bool useLauncher = true;
    };


    class Framework : public APP_Manger {
        private:
            FrameworkConfig_t _config;
            bool _using_builtin_database;
            bool _using_builtin_launcher;
            bool _inited;

            bool _run_boot_anim();
            

        public:
            Framework() :
                _using_builtin_database(true),
                _using_builtin_launcher(true),
                _inited(false) {}
            ~Framework() = default;


            /* Configs */
            inline void config(const FrameworkConfig_t& cfg) { if (_inited) { return; } else { _config = cfg;} }
            inline FrameworkConfig_t config(void) { return _config; }
            inline void setDatabase(SIMPLEKV::SimpleKV* db) { if (_inited) { return; } else { _config.database = db; } }
            inline void setBootAnim(APP_BASE* bootAnim) { if (_inited) { return; } else { _config.bootAnim = bootAnim; } }
            inline void setLauncher(APP_BASE* luancher) { if (_inited) { return; } else { _config.launcher = luancher; } }
            

            /* Framework init */
            bool init();


            /* Call this in loop to keep framework running */
            void update();

    };


}
