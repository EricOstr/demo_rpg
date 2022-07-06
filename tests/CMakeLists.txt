cmake_minimum_required(VERSION 3.8)

set(This ExampleTests)
set(Sources ExampleTests.cpp)

add_executable(${This} ${Sources} ${Headers})

# We link in the gtest, which is provided by google
target_link_libraries(
  ${This} 
  PUBLIC
  gtest_main
  demo_rpg)

# Tells CMake that this program is actually a unit test
add_test(
        NAME ${This}
        COMMAND ${This}
)

