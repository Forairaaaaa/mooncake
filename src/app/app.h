/**
 * @file app.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>

namespace Mooncake {
/**
 * @brief
 *
 */
class AppBase {
public:
    virtual ~AppBase() = default;

    /* -------------------------------------------------------------------------- */
    /*                                  App infos                                 */
    /* -------------------------------------------------------------------------- */
public:
    struct AppInfos_t {
        std::string name;
        void* icon = nullptr;
    };

    /* -------------------------------------------------------------------------- */
    /*                               Ability factory                              */
    /* -------------------------------------------------------------------------- */
public:
};
} // namespace Mooncake
