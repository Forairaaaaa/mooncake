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

// ANSI color 
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
#define _mc_log_info(fmt, args...) printf(MC_ANSI_GRN); printf(fmt, ##args); printf("\n"); printf(MC_ANSI_RST);
#define _mc_log_warnning(fmt, args...) printf(MC_ANSI_YEL); printf(fmt, ##args); printf("\n"); printf(MC_ANSI_RST);
#define _mc_log_error(fmt, args...) printf(MC_ANSI_RED); printf(fmt, ##args); printf("\n"); printf(MC_ANSI_RST);

#endif
