/**
 * @file app_manager.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.2
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app_manager.h"


using namespace MOONCAKE;


APP_BASE* APP_Manager::createApp(APP_PACKER_BASE* appPacker)
{
    if (appPacker == nullptr)
        return nullptr;

    if (!APP_Register::isAppInstalled(appPacker))
        return nullptr;

    /* Create a new app with the passing app packer */
    APP_BASE* new_app = (APP_BASE*)appPacker->newApp();
    if (new_app == nullptr)
        return nullptr;

    /* pass app packer to the new app */
    new_app->setAppPacker(appPacker);

    /* Create a new lifecycle container */
    AppLifecycle_t new_lifecycle;
    new_lifecycle.app = new_app;
    new_lifecycle.state = ON_CREATE;

    /* Push into lifecycle list */
    _app_lifecycle_list.push_back(new_lifecycle);

    /* Return the app pointer for further mangement */
    return new_app;
}


int APP_Manager::_search_app_lifecycle_list(APP_BASE* app)
{
    if (app == nullptr)
        return -1;

    for (int i = 0; i < _app_lifecycle_list.size(); i++)
    {
        if (_app_lifecycle_list[i].app == app)
            return i;
    }
    return -1;
}


bool APP_Manager::startApp(APP_BASE* app)
{
    int index = _search_app_lifecycle_list(app);
    if (index < 0)
        return false;

    /* Update state */
    switch (_app_lifecycle_list[index].state)
    {
        case ON_CREATE:
            _app_lifecycle_list[index].state = ON_RESUME;
            break;
        case ON_RESUME:
            /* Do nothing */
            break;
        case ON_RUNNING:
            /* Do nothing */
            break;
        case ON_RUNNING_BG:
            _app_lifecycle_list[index].state = ON_RESUME;
            break;
        case ON_PAUSE:
            _app_lifecycle_list[index].state = ON_RESUME;
            break;
        case ON_DESTROY:
            /* Not gonna happen */
            break;
        default:
            break;
    }

    return true;
}


bool APP_Manager::closeApp(APP_BASE* app)
{
    int index = _search_app_lifecycle_list(app);
    if (index < 0)
        return false;
    
    /* Update state */
    switch (_app_lifecycle_list[index].state)
    {
        case ON_CREATE:
            /* Do nothing */
            break;
        case ON_RESUME:
            _app_lifecycle_list[index].state = ON_PAUSE;
            break;
        case ON_RUNNING:
            _app_lifecycle_list[index].state = ON_PAUSE;
            break;
        case ON_RUNNING_BG:
            /* Do nothing */
            break;
        case ON_PAUSE:
            /* Do nothing */
            break;
        case ON_DESTROY:
            /* Not gonna happen */
            break;
        default:
            break;
    }

    return true;
}


bool APP_Manager::destroyApp(APP_BASE* app)
{
    int index = _search_app_lifecycle_list(app);
    if (index < 0)
        return false;

    return false;
}


