/**
 * @file types.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2024-04-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#define MC_VERSION "v1.1"

/* The user data type for app to convert to (void* -> MC_USER_DATA_T) */
#define MC_USER_DATA_T APP_UserData_t*

/* Define wrap for App's internal data getting */
/* Get framework's user data (App internal usage only) */
#define mcAppGetUserData() ((MC_USER_DATA_T)getUserData())

/* Get framework (App internal usage only) */
#define mcAppGetFramework() ((Mooncake*)(mcAppGetUserData()->framework))

