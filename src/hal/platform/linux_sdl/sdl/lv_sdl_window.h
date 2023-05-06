/**
 * @file lv_sdl_window.h
 *
 */
#pragma once


/*********************
 *      INCLUDES
 *********************/

#include <lvgl.h>


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_disp_t * lv_sdl_window_create(lv_coord_t hor_res, lv_coord_t ver_res);

void lv_sdl_window_set_zoom(lv_disp_t * disp, uint8_t zoom);

uint8_t lv_sdl_window_get_zoom(lv_disp_t * disp);

lv_disp_t * _lv_sdl_get_disp_from_win_id(uint32_t win_id);

void lv_sdl_window_set_title(lv_disp_t * disp, const char * title);

/**********************
 *      MACROS
 **********************/

