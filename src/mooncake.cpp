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
#include "../apps/common_apps/BootAnim_ASCII/boot_anim_ascii.h"


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


    _app_manager.createApp(new APPS::BootAnim_ASCII_Packer);
    _app_manager.destroyAllApps();


}


void Mooncake::update()
{
    _app_manager.update();
}
