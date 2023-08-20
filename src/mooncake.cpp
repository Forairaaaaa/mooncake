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
#include "simplekv/simplekv.h"
#include "spdlog/spdlog.h"


using namespace MOONCAKE;


Mooncake::~Mooncake()
{
    spdlog::warn("mooncake destruction");

    /* Destroy all apps */
    spdlog::warn("destroy all app");
    _app_manager.destroyAllApps();

    /* Free memory */
    if (_flag_free_database)
        delete _user_data->database;
    if (_flag_free_user_data)
        delete _user_data;
    if (_flag_free_boot_anim)
        delete _boot_anim;

    spdlog::warn("bye :(");
}


void Mooncake::init()
{
    spdlog::info("mooncake init :)");

    /* If user data not set */
    if (_user_data == nullptr)
    {
        spdlog::info("create userdata");
        _user_data = new APP_UserData_t;
        _flag_free_user_data = true;
    }

    /* If database not set */
    if (_user_data->database == nullptr)
    {
        spdlog::info("create database");
        _user_data->database = new SIMPLEKV::SimpleKV;
        _flag_free_database = true;
    }

    /* Setup basic data in database */
    _data_base_setup_internal();

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
        if (_app_manager.getTotalAppNum() == 0)
            break;
    }

    spdlog::info("init done");
}


void Mooncake::_data_base_setup_internal()
{
    spdlog::info("start db setup");

    /* Setup basic data with default value */
    /* Display */
    _user_data->database->Add(MC_DB_DISP_HOR, 320);
    _user_data->database->Add(MC_DB_DISP_VER, 240);

    /* Power */
    _user_data->database->Add(MC_DB_BATTERY_LEVEL, 100);
    _user_data->database->Add(MC_DB_BATTERY_IS_CHARGING, false);

    /* Call database setup callback if it's set */
    if (_database_setup_callback != nullptr)
    {
        spdlog::info("call db setup callback");
        _database_setup_callback(_user_data->database);
    }
}


void Mooncake::update()
{
    _app_manager.update();
}
