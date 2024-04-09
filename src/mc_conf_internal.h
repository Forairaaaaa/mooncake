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

#define MC_VERSION "v1.1"

/* The user data type for app to convert to (void* -> MC_USER_DATA_T) */
#define MC_USER_DATA_T APP_UserData_t*

/* Define wrap for App's internal data getting */
/* Get framework's user data (App internal usage only) */
#define mcAppGetUserData() ((MC_USER_DATA_T)getUserData())

/* Get framework's database (App internal usage only) */
#define mcAppGetDatabase() ((SIMPLEKV::SimpleKV*)(mcAppGetUserData()->database))

/* Get framework (App internal usage only) */
#define mcAppGetFramework() ((Mooncake*)(mcAppGetUserData()->framework))

#endif
