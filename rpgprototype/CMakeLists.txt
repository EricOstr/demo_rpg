cmake_minimum_required(VERSION 3.8)
project(rpgprototype)
set(CMAKE_CXX_STANDARD 17)


add_executable(rpgprototype main.cpp pch.h)

target_link_libraries(
        rpgprototype
        PRIVATE
        demo_rpg)