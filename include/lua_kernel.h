// Copyright 2019 FURGBot


#ifndef JOYSTICK_LUA_KERNEL_H
#define JOYSTICK_LUA_KERNEL_H

#include "lua.hpp"

#include <string>


namespace lua_kernel {
namespace joystick {

void newSerial(lua_State*);

namespace f180 {
    void newJoystick(lua_State*);
} // namespace f180

} // namespace joystick
} // namespace lua_kernel


#endif // JOYSTICK_LUA_KERNEL_H