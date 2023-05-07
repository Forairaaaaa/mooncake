/**
 * @file app_register.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_register.h"


namespace MOONCAKE {


    int APP_Register::install(APP_BASE* app, SIMPLEKV::SimpleKV* database, void* userData)
    {
        if (app == nullptr) {
            return -1;
        }

        /* Check multi installation */
        for (auto i : _app_list) {
            if (i.app == app) {
                return -1;
            }
        }

        /* Pass parameter */
        app->setDatabase(database);
        app->setUserData(userData);

        /* Push into App list */
        _id++;
        APPList_t new_app;
        new_app.app = app;
        new_app.id = _id;
        _app_list.push_back(new_app);

        return _id;
    }


    bool APP_Register::uninstall(uint16_t appId)
    {
        /* Find App */
        for (auto iter = _app_list.begin(); iter != _app_list.end(); iter++) {
            if (iter->id == appId) {
                _app_list.erase(iter);
                return true;
            }
        }
        return false;
    }


    int APP_Register::getAppID(APP_BASE* app)
    {
        for (auto i : _app_list) {
            if (i.app == app) {
                return i.id;
            }
        }
        return -1;
    }


    int APP_Register::getAppID(const char* name)
    {
        for (auto i : _app_list) {
            if (i.app->getName() == name) {
                return i.id;
            }
        }
        return -1;
    }


    APP_BASE* APP_Register::getApp(int id)
    {
        for (auto i : _app_list) {
            if (i.id == id) {
                return i.app;
            }
        }
        return nullptr;
    }


    APP_BASE* APP_Register::getApp(const char* name)
    {
        for (auto i : _app_list) {
            if (i.app->getName() == name) {
                return i.app;
            }
        }
        return nullptr;
    }


}
