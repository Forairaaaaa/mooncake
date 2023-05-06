# CMakeLists.txt

set(MOONCAKE_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

if (ESP_PLATFORM)
    
else()
    include(${CMAKE_CURRENT_LIST_DIR}/cmake/basic.cmake)
endif()
