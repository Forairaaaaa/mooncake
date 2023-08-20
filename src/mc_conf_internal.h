/**
 * @file mc_conf_internal.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#ifdef MC_USE_CUSTOM_CONF
    /* Try include */
    #include "../../mc_conf.h"
#else


#define MC_ENABLE_BUILTIN_APPS_LVGL__BootAnim_Gif               0
#define MC_ENABLE_BUILTIN_APPS_LVGL__Launcher_Basic             0


#endif
