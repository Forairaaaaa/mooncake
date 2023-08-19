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


/* ANSI colors */ 
#define MC_ANSI_BLK "\e[0;30m"
#define MC_ANSI_RED "\e[0;31m"
#define MC_ANSI_GRN "\e[0;32m"
#define MC_ANSI_YEL "\e[0;33m"
#define MC_ANSI_BLU "\e[0;34m"
#define MC_ANSI_MAG "\e[0;35m"
#define MC_ANSI_CYN "\e[0;36m"
#define MC_ANSI_WHT "\e[0;37m"
#define MC_ANSI_RST "\e[0m"

/* Simple logging */
#include <cstdio>
#define MC_LOG_INFO(fmt, args...)       printf(MC_ANSI_GRN); printf(fmt, ##args); printf("\n"); printf(MC_ANSI_RST);
#define MC_LOG_WARNNING(fmt, args...)   printf(MC_ANSI_YEL); printf(fmt, ##args); printf("\n"); printf(MC_ANSI_RST);
#define MC_LOG_ERROR(fmt, args...)      printf(MC_ANSI_RED); printf(fmt, ##args); printf("\n"); printf(MC_ANSI_RST);



/* The type of userdata, for apps to conovert to (void* -> MC_USER_DATA_TYPE) */
#define MC_USER_DATA_TYPE APP_UserData_t


#define MC_ENABLE_BUILTIN_APPS_LVGL__BootAnim_Gif               0
#define MC_ENABLE_BUILTIN_APPS_LVGL__Launcher_Basic             0


#endif
