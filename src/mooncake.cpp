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
#include "../apps/common_apps/boot_anim_ascii/boot_anim_ascii.h"
#include "app/app.h"
#include "spdlog/spdlog.h"

using namespace MOONCAKE;

Mooncake::~Mooncake()
{
    spdlog::warn("mooncake destruction");

    /* Free memory */
    if (_flag_free_user_data)
        delete _user_data;
    if (_flag_free_boot_anim)
        delete _boot_anim;

    spdlog::info("bye :(");
}

void Mooncake::init()
{
    spdlog::info("mooncake init :)");

    /* Init user data */
    /* If user data not set */
    if (_user_data == nullptr)
    {
        spdlog::info("create userdata");
        _user_data = new APP_UserData_t;
        _flag_free_user_data = true;
    }

    /* Copy framework's pointer into user data */
    _user_data->framework = this;

    /* Init boot anim */
    /* If boot anim not set */
    if (_boot_anim == nullptr)
    {
        spdlog::info("create boot anim");
        /* Create a default one */
        _boot_anim = new APPS::BootAnim_ASCII_Packer;
        _flag_free_boot_anim = true;
    }

    /* Start boot anim and wait till it finish */
    spdlog::info("start boot anim");
    _app_manager.destroyAllApps();
    _app_manager.startApp(_app_manager.createApp(_boot_anim));
    while (1)
    {
        _app_manager.update();
        /* If boot anim is destroyed */
        if (_app_manager.getCreatedAppNum() == 0)
            break;
    }

    spdlog::info("init done");
}

void Mooncake::update()
{
    /* Update apps' lifecycles */
    _app_manager.update();
}
