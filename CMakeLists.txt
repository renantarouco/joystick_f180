cmake_minimum_required(VERSION 3.10)
project(furgbol_joystick_f180)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Boost REQUIRED COMPONENTS system)

link_directories(${CMAKE_SOURCE_DIR}/lib/joystick-master)

include_directories("include" 
                    "lib/joystick-master"
                    "lib/lua/include"
                    "../furgbol-core/include"
                    ${Boost_INCLUDE_DIRS})

add_library(furgbol_joy
            "src/lua_kernel.cc"
            "src/system.cc")

add_library(lua53 STATIC IMPORTED)

set_target_properties(lua53 PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/lua/liblua53.a")

target_link_libraries(furgbol_joy
                    "${CMAKE_SOURCE_DIR}/../furgbol-core/lib/libfurgbol-core-io.a"
                    ${Boost_SYSTEM_LIBRARY})

add_executable(joystick_f180 "src/main.cpp")

target_link_libraries(joystick_f180
                    furgbol_joy
                    lua53
                    libjoystick.a
                    ${Boost_LIBRARIES}
                    ${CMAKE_DL_LIBS})
