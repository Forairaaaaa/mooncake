/**
 * @file hal.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../simplekv/simplekv.h"


namespace MOONCAKE {


    struct HALconfig_t {
        uint16_t dis_hor_res = 480;
        uint16_t dis_ver_res = 320;
    };


    class HAL_BASE {
        protected:
            HALconfig_t _config;
            SIMPLEKV::SimpleKV* _database;
            

        public:
            HAL_BASE() { _database = nullptr; }
            ~HAL_BASE() = default;


            /* Basic configs */
            inline HALconfig_t config(void) { return _config; }
            inline void config(const HALconfig_t& cfg) { _config = cfg; }


            /* Database API */
            inline SIMPLEKV::SimpleKV* Database() { return _database; }
            inline bool isDatabaseSet() { return _database == nullptr ? false : true; }


            /* HAL init for port to override, this will be called by mooncake init */
            virtual bool init() { return false; }


            /* Will be called by mooncake update */
            virtual void update() {}
    };


}
