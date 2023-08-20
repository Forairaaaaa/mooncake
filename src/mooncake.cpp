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
#include "spdlog/spdlog.h"


using namespace MOONCAKE;


Mooncake::~Mooncake()
{
    spdlog::warn("Mooncake destruction");

    /* Destroy all apps */
    spdlog::warn("destroy all app");
    _app_manager.destroyAllApps();

    /* Free memory */
    if (flag_free_database)
        delete _user_data->database;
    if (flag_free_user_data)
        delete _user_data;
    if (flag_free_boot_anim)
        delete _boot_anim;

    spdlog::warn("bye :(");
}


void Mooncake::init()
{
    spdlog::info("Mooncake init :)");
}


void Mooncake::update()
{
    _app_manager.update();
}
