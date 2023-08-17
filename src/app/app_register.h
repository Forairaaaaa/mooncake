/**
 * @file app_register.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.2
 * @date 2023-08-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "app.h"
#include <cstddef>
#include <iostream>
#include <vector>


namespace MOONCAKE
{
    /* App register */
    /* This class contains a list of "APP_PACKER" */
    /* Which tells the "APP_Manager" what apps do you have */
    /* "install" will add a packer into the list, "uninstall" will remove it */
    class APP_Register
    {
        protected:
            std::vector<APP_PACKER_BASE*> _app_packer_list;

        public:

            /**
             * @brief Get the list which contains installed apps' packers
             * 
             * @return const std::vector<APP_PACKER_BASE*>& 
             */
            inline const std::vector<APP_PACKER_BASE*>& getAppList() { return _app_packer_list; }

            /**
             * @brief Get the total number of the installed apps 
             * 
             * @return std::size_t 
             */
            inline std::size_t getAppNum() { return _app_packer_list.size(); }

            /**
             * @brief Install an app (Register an app packer)
             * 
             * @param appPacker 
             * @param database 
             * @param userData 
             */
            void install(APP_PACKER_BASE* appPacker, SIMPLEKV::SimpleKV* database, void* userData = nullptr);

            /**
             * @brief Uninstall an app (Remove it from the register)
             * 
             * @param app 
             * @return true ok
             * @return false failed
             */
            bool uninstall(APP_PACKER_BASE* app);
    };
}
