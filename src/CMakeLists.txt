cmake_minimum_required(VERSION 3.2)

add_executable(ip_filter main.cpp ip_filter.cpp)

set_target_properties(ip_filter ip_filter PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        )

target_include_directories(ip_filter PUBLIC ${INCLUDE_DIR})
