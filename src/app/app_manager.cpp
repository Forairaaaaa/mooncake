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


    bool APP_Manger::_add_running_app(APP_BASE* app, const APPLifecycleEvent_t& event, const APPLifecycleEvent_t& event_last)
    {
        APPManager_t new_app;
        new_app.app = app;
        new_app.event = event;
        new_app.event_last = event_last;
        _running_apps.emplace(_running_apps.begin(), new_app);
        return true;
    }


    bool APP_Manger::_remove_running_app(APP_BASE* app)
    {
        /* Iterate running Apps */
        for (auto iter = _running_apps.begin(); iter != _running_apps.end(); iter++) {
            if (iter->app == app) {
                _running_apps.erase(iter);
                return true;
            }
        }
        return false;
    }


    bool APP_Manger::startApp(APP_BASE* app)
    {
        if (app == nullptr) {
            return false;
        }

        /* If already running */
        for (auto iter = _running_apps.begin(); iter != _running_apps.end(); iter++) {
            if (iter->app == app) {
                /* Put foreground App to first element */
                std::swap(*(_running_apps.begin()), *(iter));
                /* Update foreground */
                _foreground_app = app;
                return true;
            }
        }

        /* If not, push one into running list's first one */
        _add_running_app(app, ON_CREATE, ON_SETUP);
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
                i.app->onPause();
                i.app->onDestroy();
                _remove_running_app(app);
                return true;
            }
        }
        return false;
    }


    void APP_Manger::destroyAllApps()
    {
        for (auto i : _running_apps) {
            i.app->onPause();
            i.app->onDestroy();
        }
        /* Free list */
        _running_apps.clear();
        std::vector<APPManager_t>().swap(_running_apps);
    }


    bool APP_Manger::isAppRunning(APP_BASE* app)
    {
        for (auto i : _running_apps) {
            if (i.app == app) {
                return true;
            }
        }
        return false;
    }


    /**
     * @brief FSM to implement lifecycle callbacks
     * 
     */
    void APP_Manger::update()
    {
        /**
         * Because foreground App is set to the first element, it's life cycle callback will be called firstly,
         * to avoid new App's "onCreate" or BG's resume effect FG's "onPause", "onDestroy".
         * 
         * Moreover, "onRunning", "onPause", "onDestroy" will be called at first,
         * and new App's "onCreate" or BG's "onRunningBG", "onResume" will be called next,
         * to implement a clear order.
         * 
        */
        for (auto iter = _running_apps.begin(); iter != _running_apps.end(); ) {
            
            /* On running */
            if (iter->event == ON_RUNNING) {
                /* If is foreground App, keep running */
                if (iter->app == _foreground_app) {
                    iter->app->onRunning();
                }
                /* If not, put back to background */
                else {
                    iter->event = ON_PAUSE;
                }
            }
            
            /* If App call "endApp()" internally */
            if (iter->app->isFinished()) {
                iter->app->onPause();
                iter->event = ON_DESTROY;
            }
            
            /* On pause */
            if (iter->event == ON_PAUSE) {
                iter->app->onPause();

                /* If allow backgroud running */
                if (iter->app->allowBgRunning()) {
                    iter->event = ON_RUNNING_BG;
                }
                else {
                    iter->event = ON_DESTROY;
                }
            }

            /* On destroy */
            if (iter->event == ON_DESTROY) {
                iter->app->onDestroy();
                /* Kick it out of running list */
                iter = _running_apps.erase(iter);
                continue;
            }

            /* On running backgound */
            if (iter->event == ON_RUNNING_BG) {
                /* If is foreground App, take out to foreground */
                if (iter->app == _foreground_app) {
                    iter->event = ON_RESUME;
                }
                /* If not, keep running in background */
                else {
                    iter->app->onRunningBG();
                }
            }

            /* On create */
            if (iter->event == ON_CREATE) {
                iter->app->onCreate();
                iter->event = ON_RESUME;
            }

            /* On resume */
            if (iter->event == ON_RESUME) {
                iter->app->onResume();
                iter->event = ON_RUNNING;
            }

            iter++;
        }
    }



    
    


    


}
