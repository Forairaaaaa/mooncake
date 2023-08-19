/**
 * @file mooncake_basic.cpp
 * @author Forairaaaaa
 * @brief 
 * @version 0.1
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <mooncake.h>


int main()
{
    std::cout << "[Mooncake basic example]\n";

    _mc_log_info("nihao %d %f", 123, 123.0);
    _mc_log_warnning("nihao %s %X", "asdasd", 0x99);
    _mc_log_error("ni\thao\t%ld", 123123123123);


    return 0;
}
