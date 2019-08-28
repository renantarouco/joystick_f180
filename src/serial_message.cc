// Copyright 2019 FURGBot

#include "serial_message.h"

#include <string>

namespace furgbol {
namespace joystick {

SerialMessage::SerialMessage() { clear(); }

SerialMessage::~SerialMessage() {}

void SerialMessage::serialize(std::vector<uint8_t> &buffer) {
    buffer[ROBOT_ID] = robot_id_+128;
    buffer[VEL_X] = velocity_x_;
    buffer[VEL_Y] = velocity_y_;
    buffer[VEL_THETA] = velocity_theta_;
    buffer[DIR_X] = direction_x_;
    buffer[DIR_Y] = direction_y_;
    buffer[DIR_THETA] = direction_theta_;
    buffer[DRIBBLER] = dribbler_;
    buffer[KICK] = kick_;
}

void SerialMessage::clear() {
    pkg_id_ = 0;
    msg_type_ = 0;
    robot_id_ = 0;
    velocity_x_ = 0;
    velocity_y_ = 0;
    velocity_theta_ = 0;
    direction_x_ = 0;
    direction_y_ = 0;
    direction_theta_ = 0;
    dribbler_ = 0;
    kick_ = 0;
}

std::ostream &operator << (std::ostream &stream, furgbol::joystick::SerialMessage const &message) {
    stream << "TeamProcolMessage{ " << std::endl;
    stream << "\tid: " << static_cast<int>(message.robot_id_) << std::endl;
    stream << "\tvelocity x: " << static_cast<int>(message.velocity_x_) << std::endl;
    stream << "\tvelocity y: " << static_cast<int>(message.velocity_y_) << std::endl;
    stream << "\tvelocity theta: " << static_cast<int>(message.velocity_theta_) << std::endl;
    stream << "\tdirection x: " << static_cast<int>(message.direction_x_) << std::endl;
    stream << "\tdirection y: " << static_cast<int>(message.direction_y_) << std::endl;
    stream << "\tdirection theta: " << static_cast<int>(message.direction_theta_) << std::endl;
    stream << "\tdribbler: " << static_cast<int>(message.dribbler_) << std::endl;
    stream << "\tkick: " << static_cast<int>(message.kick_) << std::endl;
    stream << "};";
    return stream;
}

void SerialMessage::setRobotId(uint8_t robot_id) {
    robot_id_ = robot_id;
}

void SerialMessage::setVelocityX(uint8_t velocity_x) {
    velocity_x_ = velocity_x;
}

void SerialMessage::setVelocityY(uint8_t velocity_y) {
    velocity_y_ = velocity_y;
}

void SerialMessage::setVelocityTheta(uint8_t velocity_theta) {
    velocity_theta_ = velocity_theta;
}

void SerialMessage::setDirectionX(uint8_t direction_x) {
    direction_x_ = direction_x;
}

void SerialMessage::setDirectionY(uint8_t direction_y) {
    direction_y_ = direction_y;
}

void SerialMessage::setDirectionTheta(uint8_t direction_theta) {
    direction_theta_ = direction_theta;
}

void SerialMessage::setDribbler(uint8_t dribbler) {
    dribbler_ = dribbler;
}

void SerialMessage::setKick(uint8_t kick) {
    kick_ = kick;
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

uint8_t SerialMessage::getVelocityX() {
    return velocity_x_;
}

uint8_t SerialMessage::getVelocityY() {
    return velocity_y_;
}

uint8_t SerialMessage::getVelocityTheta() {
    return velocity_theta_;
}

uint8_t SerialMessage::getDirectionX() {
    return direction_x_;
}

uint8_t SerialMessage::getDirectionY() {
    return direction_y_;
}

uint8_t SerialMessage::getDirectionTheta() {
    return direction_theta_;
}

uint8_t SerialMessage::getDribbler() {
    return dribbler_;
}

uint8_t SerialMessage::getKick() {
    return kick_;
}

} // namespace joystick
} // namespace furgbol