/**
 * @file ability_manager.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include "../ability/ability.h"
#include <vector>
#include <memory>

namespace Mooncake {

class AbilityManager {
public:
    /**
     * @brief 创建 Ability，返回 Ability ID
     *
     * @param ability
     * @return int
     */
    int createAbility(std::unique_ptr<AbilityBase> ability);

    /**
     * @brief 销毁指定 ID 的 Ability
     *
     * @param abilityID
     * @return true
     * @return false
     */
    bool destroyAbility(int abilityID);

    /**
     * @brief 刷新 Ability 状态，触发回调
     *
     */
    void updateAbilities();

private:
    enum AbilityState_t {
        StateGoCreate = 0,
        StateUpdating,
        StateGoDestroy,
    };

    struct AbilityInfo_t {
        int id = -1;
        AbilityState_t state = StateGoCreate;
        std::unique_ptr<AbilityBase> ability;
    };
    std::vector<AbilityInfo_t> _ability_list;
    int _next_ability_id = 0;
    std::vector<int> _available_ability_id_list;

    int get_next_ability_id();
};

} // namespace Mooncake
