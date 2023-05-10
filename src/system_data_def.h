/**
 * @file system_data_def.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 * Use define to unify baisc data's key in database(SimpleKV)
 * Framework will add them into database while init
 * It won't if no define
 */
#pragma once
#include <stdint.h>


/* System infos */
#if 1
#define MC_SYSTEM_TICKS     "_SYS_TICKS"    // uint32_t
#endif


/* Navigation */
#if 1
#define MC_KEY_MENU         "_KEY_MENU"     // bool
#define MC_KEY_HOME         "_KEY_HOME"     // bool
#define MC_KEY_BACK         "_KEY_BACK"     // bool
#define MC_KEY_POWER        "_KEY_PWR"      // bool
#endif


/* Time */
#if 1
#define MC_TIME             "_TIME"         // MOONCAKE::DataTime_t
namespace MOONCAKE {
    struct DataTime_t {
        uint8_t sec;		/* Seconds.	[0-60] (1 leap second) */
        uint8_t min;		/* Minutes.	[0-59] */
        uint8_t hour;		/* Hours.	[0-23] */
        uint8_t mday;		/* Day.		[1-31] */
        uint8_t mon;		/* Month.	[0-11] */
        uint8_t wday;		/* Day of week.	[0-6] */
        int year;			/* Year	- 1900.  */
        long int gmtoff;	/* Seconds east of UTC.  */
    };
}
#endif


/* Hardware */
#if 1
#define MC_DISP_HOR         "_DIS_HOR"      // int16_t
#define MC_DISP_VER         "_DIS_VER"      // int16_t
#define MC_DISP_BRIGHTNESS  "_DIS_BRI"      // uint8_t
#endif
