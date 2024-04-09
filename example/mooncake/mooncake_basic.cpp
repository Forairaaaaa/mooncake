/**
 * @file mooncake_basic.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2023-08-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "spdlog/spdlog.h"
#include <cstdint>
#include <iostream>
#include <mooncake.h>

using namespace MOONCAKE;

int main()
{
    std::cout << "[Mooncake basic example]\n";

    Mooncake mooncake;

    mooncake.init();

    for (int i = 0; i < 66; i++)
        mooncake.update();

    return 0;
}
