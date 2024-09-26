/**
 * @file worker_ability.cpp
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

void WorkerAbility::baseCreate()
{
    onCreate();
}

void WorkerAbility::baseUpdate()
{
    /* ----------------------------------- 状态机 ---------------------------------- */
    switch (current_state) {
        case StateGoResume: {
            onResume();
            current_state = StateRunning;
            break;
        }
        case StateRunning: {
            onRunning();
            break;
        }
        case StateGoPause: {
            onPause();
            current_state = StatePausing;
            break;
        }
        case StatePausing: {
            // Do nothing
            break;
        }
        default:
            break;
    }
}

void WorkerAbility::baseDestroy()
{
    onDestroy();
}

void WorkerAbility::pause()
{
    current_state = StateGoPause;
}

void WorkerAbility::resume()
{
    current_state = StateGoResume;
}
