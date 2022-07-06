cmake_minimum_required(VERSION 3.21)
project(rpgprototype1)
set(CMAKE_CXX_STANDARD 17)

#enable_testing()

add_subdirectory(googletest)
add_subdirectory(tests)

add_subdirectory(demo_rpg) # add library first, since below we are linking against it
add_subdirectory(rpgprototype)
