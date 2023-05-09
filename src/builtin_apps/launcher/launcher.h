/**
 * @file launcher.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include "../../app/app.h"
#include "../../framework/framework.h"


namespace MOONCAKE {
    namespace BUILTIN_APP {

    
        class Launcher : public APP_BASE {
            private:
                Framework* _framework;

            public:
                Launcher() : _framework(nullptr) {}
                ~Launcher() = default;


                /**
                 * @brief Lifecycle callbacks for derived to override
                 * 
                 */
                /* Setup App configs, called when App "install()" */
                void onSetup();

                /* Life cycle */
                void onCreate();
                void onResume();
                void onRunning();
                void onRunningBG();
                void onPause();
                void onDestroy();
            
        };


    }
}
