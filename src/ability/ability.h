/**
 * @file ability.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

namespace Mooncake {
enum AbilityType_t {
    BasicAbility = 0,
    UIAbility,
    WorkerAbility,
};

class BasicAbility {
public:
    virtual ~BasicAbility() = default;

    /* -------------------------------------------------------------------------- */
    /*                         Basic life cycle callbacks                         */
    /* -------------------------------------------------------------------------- */
public:
    virtual void onCreate() {}
    virtual void onUpdate() {}
    virtual void onDestroy() {}
};

} // namespace Mooncake