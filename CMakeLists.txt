cmake_minimum_required(VERSION 3.29)
project(RSAproject)

set(CMAKE_CXX_STANDARD 20)


add_executable(RSAproject main.cpp
        rsa.cpp
        rsa.h)


find_package(Boost REQUIRED)

target_link_libraries(RSAproject Boost::boost)
