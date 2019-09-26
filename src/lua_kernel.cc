// Copyright 2019 FURGBot

#include "lua_kernel.h"

namespace lua_kernel {

void printError(lua_State *lua_state) {
    const char *message = lua_tostring(lua_state, -1);
    printf("\n\n**[ERROR]: %s\n", message);
    lua_pop(lua_state, -1);
}

void joystick::newSerial(lua_State *lua_state, ManualControl joy) {
    lua_pushstring(lua_state, "serial_port");
    lua_gettable(lua_state, 1);
    joy.setSerialPort(lua_tostring(lua_state, -1));
}

void joystick::f180::newJoystick(lua_State *lua_state, ManualControl joy) {
    lua_pushstring(lua_state, "message_type");
    lua_gettable(lua_state, 1);
    joy.setMsgType((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "robot_id");
    lua_gettable(lua_state, 1);
    joy.setRobotId((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "communication_frequency");
    lua_gettable(lua_state, 1);
    joy.setCommunicationFrequency((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "min_axis_value");
    lua_gettable(lua_state, 1);
    joy.setMinAxisValue((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "max_axis_value");
    lua_gettable(lua_state, 1);
    joy.setMaxAxisValue((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "max_linear_velocity");
    lua_gettable(lua_state, 1);
    joy.setMaxLinearVelocity((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "max_angular_velocity");
    lua_gettable(lua_state, 1);
    joy.setMaxAngularVelocity((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "dribbler_velocity");
    lua_gettable(lua_state, 1);
    joy.setDribblerVelocity((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "kick_power");
    lua_gettable(lua_state, 1);
    joy.setKickPower((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "kick_times");
    lua_gettable(lua_state, 1);
    joy.setKickTimes((int)lua_tonumber(lua_state, -1));

    lua_pushstring(lua_state, "pass_power");
    lua_gettable(lua_state, 1);
    joy.setPassPower((int)lua_tonumber(lua_state, -1));
}

} // namespace lua_kernel