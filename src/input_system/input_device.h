/**
 * @file input_device.h
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <string>


namespace MOONCAKE
{   
    /* This is a enum to indentify the tpye of the input device */
    enum InputDeviceType_t
    {
        Input_Custom = 0,
        Input_Button,
        Input_TouchPad,
        Input_Encoder,
        Input_Mouse,
        Input_Keyboard
    };

    /* Input device base */
    /* This is a base class for all kinds of input device */
    class INPUT_DEVICE_BASE
    {
        private:
            /* Device type */
            InputDeviceType_t _device_type;

            /* Device name */
            std::string _name;

            /* User data */
            void* _user_data;


        protected:
            /* Can only be set internally */
            inline void setDeviceType(const InputDeviceType_t& deviceType) { _device_type = deviceType; }
            

        public:
            INPUT_DEVICE_BASE() :
                _device_type(Input_Custom),
                _user_data(nullptr)
                {}

            /**
             * @brief Get the class pointer (base type)
             * 
             * @return INPUT_DEVICE_BASE* 
             */
            inline INPUT_DEVICE_BASE* getAddr() { return this; }

            /**
             * @brief Set device name
             * 
             * @param name 
             */
            inline void setDeviceName(const std::string& name) { _name = name; }

            /**
             * @brief Get device name
             * 
             * @return const std::string& 
             */
            inline const std::string& getDeviceName() { return _name; }

            /**
             * @brief Get device type
             * 
             * @return const InputDeviceType_t& 
             */
            inline const InputDeviceType_t& getDeviceType() { return _device_type; }
    };
}
