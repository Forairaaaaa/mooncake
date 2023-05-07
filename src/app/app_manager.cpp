/**
 * @file app_manager.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_manager.h"


namespace MOONCAKE {


    bool APP_Manger::startApp(APP_BASE* app)
    {
        if (app == nullptr) {
            return false;
        }

        /* If already running */
        for (auto i : _running_apps) {
            if (i.app == app) {
                /* Update foreground */
                _foreground_app = app;
                i.event = ON_RUNNING;
                return true;
            }
        }

        /* If not, push into running Apps */
        APPManager_t new_app;
        new_app.app = app;
        new_app.event = ON_CREATE;
        new_app.event_last = ON_SETUP;
        _running_apps.push_back(new_app);
        /* Update foreground */
        _foreground_app = app;

        return true;
    }


    bool APP_Manger::closeApp(APP_BASE* app)
    {
        if (app == nullptr) {
            return false;
        }

        /* Search in running list */
        for (auto i : _running_apps) {
            if (i.app == app) {
                /* If not allow backgroud running */
                if (!app->allowBgRunning()) {
                    return destroyApp(app);
                }

                /* Put it to background */
                i.event = ON_PAUSE;
                return true;
            }
        }
        return false;
    }


    bool APP_Manger::destroyApp(APP_BASE* app)
    {
        if (app == nullptr) {
            return false;
        }

        /* Search in running Apps */
        for (auto i : _running_apps) {
            if (i.app == app) {
                i.event = ON_DESTROY;
                return true;
            }
        }
        return false;
    }


    /**
     * @brief FSM to call App lifecycle callback 
     * 
     */
    void APP_Manger::update()
    {
        /* Iterate running Apps */
        for (auto iter = _running_apps.begin(); iter != _running_apps.end(); iter++) {

        }
    }


}
