/**
 * @file framework.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "framework.h"
#include "../builtin_apps/builtin_apps.h"


namespace MOONCAKE {


    bool Framework::_run_boot_anim()
    {
        /* If boot anim is not set */
        if (_config.bootAnim == nullptr) {
            _config.bootAnim = new BUILTIN_APP::Boot_Anim;
            if (_config.bootAnim == nullptr) {
                return false;
            }
        }
        /* Run Anim until finished */
        install(_config.bootAnim, nullptr, nullptr);
        startApp(_config.bootAnim);
        while (1) {
            APP_Manger::update();
            if (!isAppRunning(_config.bootAnim)) {
                break;
            }
        }
        return true;
    }


    bool Framework::init()
    {
        if (_inited) {
            return false;
        }

        /* Clear running Apps */
        destroyAllApps();

        /* If database is set */
        if (_config.database != nullptr) {
            _using_builtin_database = false;
        }
        else {
            _config.database = new SIMPLEKV::SimpleKV;
            if (_config.database == nullptr) {
                return false;
            }
        }

        /* Boot anim */
        if (_config.playBootAnim) {
            if (!_run_boot_anim()) {
                return false;
            }
        }
        
        /* If dont use launcher */
        if (!_config.useLauncher) {
            _inited = true;
            return true;
        }

        /* If launcher is set */
        if (_config.launcher != nullptr) {
            _using_builtin_launcher = false;
        }
        else {
            _config.launcher = new BUILTIN_APP::Launcher;
            if (_config.launcher == nullptr) {
                return false;
            }
        }
        
        /* Install launcher, and pass framework's pointer as userdata */
        install(_config.launcher, _config.database, (void*)this);
        /* Start launcher */
        startApp(_config.launcher);

        _inited = true;
        return true;
    }


    void Framework::update()
    {
        


        /* Update App manager */
        APP_Manger::update();
    }
    


}
