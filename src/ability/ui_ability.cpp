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
        case StateGoShow: {
            onShow();
            current_state = StateForeground;
            break;
        }
        case StateForeground: {
            onForeground();
            break;
        }
        case StateGoHide: {
            onHide();
            current_state = StateBackground;
            break;
        }
        case StateBackground: {
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
    current_state = StateGoShow;
}

void UIAbility::hide()
{
    current_state = StateGoHide;
}
