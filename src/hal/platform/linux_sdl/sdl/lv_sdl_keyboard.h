/**
 * @file lv_sdl_keyboard.h
 *
 */
#pragma once

/*********************
 *      INCLUDES
 *********************/
#include "lv_sdl_window.h"

/*********************
 *      DEFINES
 *********************/
#ifndef KEYBOARD_BUFFER_SIZE
#define KEYBOARD_BUFFER_SIZE 32
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_indev_t * lv_sdl_keyboard_create(void);

/**********************
 *      MACROS
 **********************/
