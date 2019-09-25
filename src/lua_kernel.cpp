// Copyright 2019 FURGBot

#include "lua_kernel.h"

namespace lua_kernel {

void printError(lua_State *lua_state_) {
    const char *message = lua_tostring(lua_state_, -1);
    printf("\n\n**[ERROR]: %s\n", message);
    lua_pop(lua_state_, -1);
}

namespace joystick {


void newSerial(lua_State *lua_state) {
    
}


namespace f180 {

void newJoystick(lua_State *lua_state) {}

} // namespace f180
} // namespace joystick
} // namespace lua_kernel