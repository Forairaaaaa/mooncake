/**
 * @file framework.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../app/app_manager.h"


namespace MOONCAKE {


    class Framework : public APP_Manger {
        private:
            SIMPLEKV::SimpleKV* _database;
            bool _internal_database;

        public:
            Framework(SIMPLEKV::SimpleKV* database = nullptr);
            ~Framework();




            /* Call this in loop to keep framework running */
            void update();

    };


}
