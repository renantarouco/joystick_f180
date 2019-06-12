// Copyright 2019 FURGBot

#include "serial_message.h"

#include <string>

namespace furgbol {
namespace joystick {

SerialMessage::SerialMessage() {}

SerialMessage::SerialMessage(uint16_t pkg_id, uint8_t msg_type, uint8_t robot_id, uint8_t *wheels_vel, uint8_t dribbler, uint8_t kick) {
    pkg_id_ = pkg_id;
    msg_type_ = msg_type;
    robot_id_ = robot_id;
    wheels_vel_[0] = wheels_vel[0];
    wheels_vel_[1] = wheels_vel[1];
    wheels_vel_[2] = wheels_vel[2];
    wheels_vel_[3] = wheels_vel[3];
    dribbler_ = dribbler;
    kick_ = kick;
}

SerialMessage::~SerialMessage() {}

void SerialMessage::serialize(char *buffer) {
    buffer[PKG_ID_FIRST] = (char)(pkg_id_ >> 8) | 0;
    buffer[PKG_ID_SECOND] = (char)pkg_id_ | 0;
    buffer[MSG_TYPE] = (char)msg_type_;
    buffer[ROBOT_ID] = (char)robot_id_;
    buffer[VEL_WHEEL_ONE] = (char)wheels_vel_[VEL_WHEEL_ONE];
    buffer[VEL_WHEEL_TWO] = (char)wheels_vel_[VEL_WHEEL_TWO];
    buffer[VEL_WHEEL_THREE] = (char)wheels_vel_[VEL_WHEEL_THREE];
    buffer[VEL_WHEEL_FOUR] = (char)wheels_vel_[VEL_WHEEL_FOUR];
    buffer[DRIBBLER] = (char)dribbler_;
    buffer[KICK] = (char)kick_;
}

uint16_t SerialMessage::getPkgId() {
    return pkg_id_;
}

uint8_t SerialMessage::getMsgType() {
    return msg_type_;
}

uint8_t SerialMessage::getRobotId() {
    return robot_id_;
}

uint8_t *SerialMessage::getWheelsVel() {
    return wheels_vel_;
}

uint8_t SerialMessage::getDribbler() {
    return dribbler_;
}

uint8_t SerialMessage::getKick() {
    return kick_;
}

} // namespace joystick
} // namespace furgbol