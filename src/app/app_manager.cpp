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

                /* If App is running on foregound  */
                if (iter->event == ON_RUNNING) {
                    return true;
                }

                /* Send event */
                iter->event = ON_RESUME;
                /* Update foreground */
                _foreground_app = app;
                /* Setup flag to update the first element after next update */
                _update_first_element = true;                
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
        for (auto iter = _running_apps.begin(); iter != _running_apps.end(); iter++) {
            if (iter->app == app) {
                
                /* If already running on background */
                if (iter->event == ON_RUNNING_BG) {
                    return true;
                }

                iter->event = ON_PAUSE;
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

        /* Search in running list */
        for (auto iter = _running_apps.begin(); iter != _running_apps.end(); iter++) {
            if (iter->app == app) {
                iter->event = ON_PAUSE_DESTROY;
                return true;
            }
        }
        return false;
    }


    void APP_Manger::destroyAllApps()
    {
        for (auto iter = _running_apps.begin(); iter != _running_apps.end(); iter++) {
            iter->app->onPause();
            iter->app->onDestroy();
        }
        /* Free list */
        _running_apps.clear();
        std::vector<APPManager_t>().swap(_running_apps);
    }


    bool APP_Manger::isAppRunning(APP_BASE* app)
    {
        for (auto iter = _running_apps.begin(); iter != _running_apps.end(); iter++) {
            if (iter->app == app) {
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
         * Because foreground App is set to be the first element, it's life cycle callbacks will be called firstly,
         * to avoid new App's "onCreate" or BG's "onResume" effect FG's "onPause", "onDestroy".
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
                /* End it */
                iter->app->onPause();
                iter->event = ON_DESTROY;
            }
            
            /* On pause */
            if (iter->event == ON_PAUSE) {
                iter->app->onPause();

                /* If allow backgroud running */
                if (iter->app->isAllowBgRunning()) {
                    iter->event = ON_RUNNING_BG;
                }
                else {
                    iter->event = ON_DESTROY;
                }
            }

            /* On pause destroy */
            if (iter->event == ON_PAUSE_DESTROY) {
                iter->app->onPause();
                iter->event = ON_DESTROY;
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
                iter->app->onRunningBG();
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
        
        /* If need to update first element of running list */
        if (_update_first_element) {
            _update_first_element = false;
            /* Find FG App */
            for (auto iter = _running_apps.begin(); iter != _running_apps.end(); iter++) {
                if (iter->app == _foreground_app) {
                    /* Swap it to the first one */
                    std::swap(*(_running_apps.begin()), *(iter));
                    break;
                }
            }
        }

    }



    
    


    


}
