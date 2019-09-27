// Copyright 2019 FURGBot


#ifndef JOYSTICK_LUA_KERNEL_H
#define JOYSTICK_LUA_KERNEL_H

#include "lua.hpp"
#include "manual_control.h"

#include <string>


namespace lua_kernel {

void printError(lua_State *lua_state);

namespace joystick {

void newSerial(lua_State *lua_state, ManualControl joy);

namespace f180 {

void newJoystick(lua_State *lua_state, ManualControl joy);

}

}


} // namespace lua_kernel


#endif // JOYSTICK_LUA_KERNEL_H