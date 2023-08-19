/**
 * @file mooncake.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "mooncake.h"
#include "mc_conf_internal.h"


using namespace MOONCAKE;


Mooncake::~Mooncake()
{
    MC_LOG_WARNNING("Mooncake destruction");

    /* Destroy all apps */
    MC_LOG_WARNNING("destroy all apps");
    _app_manager.destroyAllApps();

    /* Free memory */
    if (flag_free_database)
        delete _user_data->database;
    if (flag_free_user_data)
        delete _user_data;
    if (flag_free_boot_anim)
        delete _boot_anim;

    MC_LOG_WARNNING("bye :(");
}


void Mooncake::init()
{
    MC_LOG_INFO("Mooncake init");
}


void Mooncake::update()
{
    _app_manager.update();
}
