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
#include "app/app.h"
#include "spdlog/spdlog.h"
#include <cstdio>

using namespace MOONCAKE;

Mooncake::~Mooncake()
{
    _free_components();
    spdlog::info("mooncake destroyed");
    spdlog::info("bye :)");
}

void Mooncake::_free_components()
{
    if (_data.app_manager != nullptr)
        delete _data.app_manager;
    if (_data.app_register != nullptr)
        delete _data.app_register;
}

static const char* _mooncake_ascii_logo = R"(
 _____ _____ _____ _____ _____ _____ _____ _____
|     |     |     |   | |     |  _  |  |  |   __|
| | | |  |  |  |  | | | |   --|     |    -|   __|
|_|_|_|_____|_____|_|___|_____|__|__|__|__|_____|
)";

void Mooncake::_welcome_log()
{
    printf("%s", _mooncake_ascii_logo);
    printf("\n- @author Forairaaaaa\n");
    printf("- @version " MC_VERSION "\n");
    printf("- @build at " __TIME__ " " __DATE__ "\n\n");
}

void Mooncake::init()
{
    spdlog::info("mooncake init :)");

    if (_data.app_register != nullptr)
    {
        spdlog::warn("mooncake reinit :(");
        _free_components();
    }

    _data.app_register = new APP_Register;
    _data.app_manager = new APP_Manager;

    _welcome_log();
    spdlog::info("done");
}

void Mooncake::update()
{
    // Update manager
    _data.app_manager->update();
}
