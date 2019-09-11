cmake_minimum_required(VERSION 3.10)
project(furgbol_joystick_f180)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost REQUIRED COMPONENTS system)

link_directories(${CMAKE_SOURCE_DIR}/lib/joystick-master)

include_directories("include" "lib/joystick-master" "../furgbol-core/include" ${Boost_INCLUDE_DIRS})

add_library(furgbol_joy "src/manual_control.cc" "src/parameters.cc" "include/json.hpp")

target_link_libraries(furgbol_joy ${Boost_SYSTEM_LIBRARY} "/home/miguel/Workspaces/furgbot/furgbol-core/lib/libfurgbol-core-io.a")

add_executable(joystick_f180 "src/main.cpp")

target_link_libraries(joystick_f180 furgbol_joy ${Boost_LIBRARIES} libjoystick.a)
