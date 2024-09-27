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

    /**
     * @brief 获取 Ability 实例原始指针，以便从外部触发生命周期变化，或者自定义 API 调用，最不安全的一集
     *
     * @param abilityID
     * @return AbilityBase*
     */
    AbilityBase* getAbilityInstance(int abilityID);

    /**
     * @brief 获取 Ability 类型
     *
     * @param abilityID
     * @return AbilityType::Type_t
     */
    AbilityType::Type_t getAbilityType(int abilityID);

    /* -------------------------------------------------------------------------- */
    /*                             UI Ability API Wrap                            */
    /* -------------------------------------------------------------------------- */
    // 对外的、安全的 UI Ability 状态切换接口

    /**
     * @brief 将 UI Ability 从后台切回前台
     *
     * @param abilityID
     * @return true
     * @return false
     */
    bool UIAbilityShow(int abilityID);

    /**
     * @brief 将 UI Ability 从前台切到后台
     *
     * @param abilityID
     * @return true
     * @return false
     */
    bool UIAbilityHide(int abilityID);

protected:
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
