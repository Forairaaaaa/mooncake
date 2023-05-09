/**
 * @file framework.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "framework.h"


namespace MOONCAKE {


    Framework::Framework(SIMPLEKV::SimpleKV* database)
    {
        _internal_database = false;

        /* If pass in not available */
        if (database == nullptr) {
            _internal_database = true;
            _database = new SIMPLEKV::SimpleKV;
        }
    }


    Framework::~Framework()
    {
        /* Free resources */
        if (_internal_database) {
            delete _database;
        }
    }


    void Framework::update()
    {



        /* Update App manager */
        APP_Manger::update();
    }
    


}
