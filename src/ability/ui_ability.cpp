/**
 * @file ui_ability.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "ability.h"

using namespace Mooncake;

void UIAbility::baseCreate()
{
    onCreate();
}

void UIAbility::baseUpdate()
{
    /* ----------------------------------- 状态机 ---------------------------------- */
    switch (current_state) {
        case StateOnShow: {
            onShow();
            current_state = StateOnForeground;
            break;
        }
        case StateOnForeground: {
            onForeground();
            break;
        }
        case StateOnHide: {
            onHide();
            current_state = StateOnBackground;
            break;
        }
        case StateOnBackground: {
            onBackground();
            break;
        }
        default:
            break;
    }
}

void UIAbility::baseDestroy()
{
    onDestroy();
}

void UIAbility::show()
{
    current_state = StateOnShow;
}

void UIAbility::hide()
{
    current_state = StateOnHide;
}
