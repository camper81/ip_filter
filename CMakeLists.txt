cmake_minimum_required(VERSION 3.20)
project(ip_filter)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@mail.com)

include(CPack)

install(TARGETS ip_filter RUNTIME DESTINATION bin)
