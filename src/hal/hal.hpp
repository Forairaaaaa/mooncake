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

    class HAL_BASE {
        protected:
            SIMPLEKV::SimpleKV* _database;

        public:
            HAL_BASE() { _database = nullptr; }
            ~HAL_BASE() = default;

            /* Database API */
            inline SIMPLEKV::SimpleKV* Database() { return _database; }
            inline bool isDatabaseSet() { return _database == nullptr ? false : true; }

            /* HAL init for port to override, this will be called by mooncake init */
            virtual bool init() { return false; }
            
    };

}
