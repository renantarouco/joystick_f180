// Copyright 2019 FURGBot

#ifndef JOYSTICK_SERIAL_MESSAGE_H
#define JOYSTICK_SERIAL_MESSAGE_H

#include <stdint.h>

namespace furgbol {
namespace joystick {

enum SerialMessageHeaderFlags {
    PKG_ID_FIRST = 0, PKG_ID_SECOND = 1, MSG_TYPE = 2, ROBOT_ID = 3, VEL_WHEEL_ONE = 4,
    VEL_WHEEL_TWO = 5, VEL_WHEEL_THREE = 6, VEL_WHEEL_FOUR = 7, DRIBBLER = 8, KICK = 9
};

class SerialMessage {
    private:
        uint16_t pkg_id_;
        uint8_t msg_type_;
        uint8_t robot_id_;
        uint8_t wheels_vel_[4];
        uint8_t dribbler_;
        uint8_t kick_;

    public:
        SerialMessage();
        SerialMessage(uint16_t pkg_id, uint8_t msg_type, uint8_t robot_id, uint8_t *wheels_vel, uint8_t dribbler, uint8_t kick);
        ~SerialMessage();

        void serialize(char *buffer);

        uint16_t getPkgId();
        uint8_t getMsgType();
        uint8_t getRobotId();
        uint8_t *getWheelsVel();
        uint8_t getDribbler();
        uint8_t getKick();
};

}  // namespace joystick
}  // namespace furgbol

#endif // JOYSTICK_SERIAL_MESSAGE_H