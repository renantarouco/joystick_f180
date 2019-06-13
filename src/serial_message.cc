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

void SerialMessage::serialize(std::vector<unsigned char> &buffer) {
    /*std::cout<<"=========================PACOTE====================================\n"<<std::endl;
    printf("%u\n",robot_id_);
    printf("%u\n",wheels_vel_[0]);
    printf("%u\n",wheels_vel_[1]);
    printf("%u\n",wheels_vel_[2]);
    printf("%u\n",wheels_vel_[3]);
    printf("%u\n",dribbler_);
    printf("%u\n",kick_);*/
    buffer[ROBOT_ID] = robot_id_;
    buffer[VEL_WHEEL_ONE] = wheels_vel_[0];
    buffer[VEL_WHEEL_TWO] = wheels_vel_[1];
    buffer[VEL_WHEEL_THREE] = wheels_vel_[2];
    buffer[VEL_WHEEL_FOUR] = wheels_vel_[3];
    buffer[DIRECTION] = 0;
    buffer[DIRECTION] = wheels_dir_[3] << 3 | wheels_dir_[2] << 2 | wheels_dir_[1] << 1 | wheels_dir_[0];
    buffer[DRIBBLER] = dribbler_;
    buffer[KICK] = kick_;
}

void SerialMessage::clear() {
    pkg_id_ = 0;
    msg_type_ = 0;
    robot_id_ = 0;
    wheels_vel_[0] = 0;
    wheels_vel_[1] = 0;
    wheels_vel_[2] = 0;
    wheels_vel_[3] = 0;
    dribbler_ = 0;
    kick_ = 0;
}

std::ostream &operator << (std::ostream &stream, furgbol::joystick::SerialMessage const &message)
{
    stream << "TeamProcolMessage{ " << std::endl;
    stream << "\tid: " << static_cast<int>(message.robot_id_) << std::endl;
    stream << "\twheels_velocity: [ ";
    stream << static_cast<int>(message.wheels_vel_[0]) << ", ";
    stream << static_cast<int>(message.wheels_vel_[1]) << ", ";
    stream << static_cast<int>(message.wheels_vel_[2]) << ", ";
    stream << static_cast<int>(message.wheels_vel_[3]);
    stream << "]" << std::endl;
    stream << "\twheels_direction: [ ";
    stream << static_cast<int>(message.wheels_dir_[0]) << ", ";
    stream << static_cast<int>(message.wheels_dir_[1]) << ", ";
    stream << static_cast<int>(message.wheels_dir_[2]) << ", ";
    stream << static_cast<int>(message.wheels_dir_[3]);
    stream << "]" << std::endl;
    stream << "\tdribbler: " << static_cast<int>(message.dribbler_) << std::endl;
    stream << "\tkick: " << static_cast<int>(message.kick_) << std::endl;
    stream << "};";
    return stream;
}

void SerialMessage::setRobotId(uint8_t robot_id) {
    robot_id_ = robot_id;
}

void SerialMessage::setWheelsVel(uint8_t* wheels_vel) {
    wheels_vel_[0] = wheels_vel[0];
    wheels_vel_[1] = wheels_vel[1];
    wheels_vel_[2] = wheels_vel[2];
    wheels_vel_[3] = wheels_vel[3];
}

void SerialMessage::setWheelsDir(uint8_t* wheels_dir) {
    wheels_dir_[0] = wheels_dir[0];
    wheels_dir_[1] = wheels_dir[1];
    wheels_dir_[2] = wheels_dir[2];
    wheels_dir_[3] = wheels_dir[3];
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

uint8_t *SerialMessage::getWheelsVel() {
    return wheels_vel_;
}

uint8_t *SerialMessage::getWheelsDir() {
    return wheels_dir_;
}

uint8_t SerialMessage::getDribbler() {
    return dribbler_;
}

uint8_t SerialMessage::getKick() {
    return kick_;
}

} // namespace joystick
} // namespace furgbol